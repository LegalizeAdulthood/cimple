/*
**==============================================================================
**
** Copyright (c) 2010 Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

/*************************************************************************** 
        Display tools for cmpi that are compiled only in compile debug mode
        Includes:
            CMPIInstance and CMPIObjectPath
                output to file
                format to string
                log
****************************************************************************/

#include "CMPIUtils.h"
#include <cimple/config.h>
#include <string.h>

// Export cimple_cmpi_adapter() only for shared library.
#ifdef CIMPLE_STATIC
# define CIMPLE_ADAPTER_LINKAGE CIMPLE_HIDE
#else
# define CIMPLE_ADAPTER_LINKAGE CIMPLE_EXPORT
#endif


#ifndef CMPIINLINE
# if defined(__GNUC__)
#  define CMPIINLINE static __inline__
# elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#  define CMPIINLINE static inline
# else
#  define CMPIINLINE static
# endif
#endif

CIMPLE_NAMESPACE_BEGIN

static const char* CMPIChars(const CMPIString* s)
{
    return s ?  CMGetCharsPtr(s, NULL) : NULL;
}

static CMPIBoolean CMPIOKAY(CMPIStatus st)
{
    return st.rc == CMPI_RC_OK;
}

#define CMPIRETURN(CODE) return _return(CMPI_RC_##CODE)
static void _setStatus(CMPIStatus* status, CMPIrc rc)
{
    if (status)
    {
        status->rc = rc;
        status->msg = NULL;
    }
}

static CMPIStatus _return(CMPIrc RC)
{
    CMPIStatus status;
    _setStatus(&status, RC);
    return status;
}

// Indent str by defined value
static void _indent(String& str, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
    {
        str.append("    ");
    }
}

// Append formated scalar value to str
static void _print_scalar(
    String& str,            // append format to this String
    const CMPIData* cd, 
    size_t n)
{
    if (cd->state & CMPI_nullValue)
    //if (CMIsNullValue(cd))
    {
        str.append("null");
        return;
    }

    String strl = "";
    switch (cd->type & ~CMPI_ARRAY)
    {
        case CMPI_boolean:
            strl = (cd->value.boolean ? "true" : "false");
            break;
        case CMPI_uint8:
            strl = string_printf("%u", cd->value.uint8);
            break;
        case CMPI_sint8:
            strl = string_printf("%d", cd->value.sint8);
            break;
        case CMPI_uint16:
            strl = string_printf("%u", cd->value.uint16);
            break;
        case CMPI_sint16:
            strl = string_printf("%d", cd->value.sint16);
            break;
        case CMPI_uint32:
            strl = string_printf("%u", cd->value.uint32);
            break;
        case CMPI_sint32:
            strl = string_printf("%d", cd->value.sint32);
            break;
        case CMPI_uint64:
            string_printf("%llu", cd->value.uint64);
            break;
        case CMPI_sint64:
            strl = string_printf("%lld", cd->value.sint64);
            break;
        case CMPI_real32:
            strl = string_printf("%f", cd->value.real32);
            break;
        case CMPI_real64:
            strl = string_printf("%f", cd->value.real64);
            break;
        case CMPI_char16:
            strl = string_printf("%u", cd->value.char16);
            break;
        case CMPI_string:
            /* ATTN: improve string formatting */
            strl = string_printf("\"%s\"", CMPIChars(cd->value.string));
            break;
        case CMPI_dateTime:
            strl = string_printf("%s", 
                CMPIChars(CMGetStringFormat(cd->value.dateTime, NULL)));
            break;
        case CMPI_ref:
            printCMPIObjectPath(strl, cd->value.ref, n);
            break;
        case CMPI_instance:
            printCMPIInstance(strl, cd->value.inst, n);
            break;
    }
    str.append(strl);
}

static void _print_array(String& str, const CMPIData* cd, size_t n)
{
    CMPICount count;
    CMPIArray* array;
    CMPICount i;

    if (cd->state & CMPI_nullValue)
    //if (CMIsNullValue(cd))
    {
        str.append("null");
        return;
    }

    if (!(array = cd->value.array))
        return;

    str.append("{");

    count = CMGetArrayCount(array, NULL);
    for (i = 0; i < count; i++)
    {
        CMPIStatus st = { CMPI_RC_OK, NULL };
        CMPIData cd = CMGetArrayElementAt(array, i, &st);

        if (CMPIOKAY(st))
        {
            _print_scalar(str, &cd, n);

            if (i + 1 != count)
                str.append(", ");
        }
    }

    str.append("}");
}
static void _print_value(String& str, const CMPIData* cd, size_t indent)
{
    if (cd->type & CMPI_ARRAY)
        _print_array(str, cd, indent);
    else
        _print_scalar(str, cd, indent);
}

// output formatted CMPIObjectPath to File
CMPIStatus printCMPIObjectPath(
    FILE* os,
    const CMPIObjectPath* self,
    size_t indent )
{
    String str = "";
    CMPIStatus st =  printCMPIObjectPath(
        str, self, indent);
    // TODO show status returned if bad
    fprintf(os, "%s", str.c_str());
    return st;
}

// output formatted CMPIObjectPath to stdout
CMPIStatus printCMPIObjectPath(
    const CMPIObjectPath* self,
    size_t indent )
{
    String str = "";
    CMPIStatus st =  printCMPIObjectPath(
        str, self, indent);
    printf("%s", str.c_str());
    return st;
}

// Output the formatted object path to the log file as DEBUG output
CMPIStatus logCMPIObjectPath(
    const char* file, int line,
    const CMPIObjectPath* self,
    size_t indent )
{
    String str = "";
    CMPIStatus st =  printCMPIObjectPath(
        str, self, indent);
    // TODO show status returned if bad.
    log(LL_DBG, file, line, "CMPIObjectPath: %s", str.c_str());

    return st;
}

// print CMPIObjectPath to a String
CMPIStatus printCMPIObjectPath(
    String& str,
    const CMPIObjectPath* self, 
    size_t indent )
{
    CMPIString* cn;
    CMPIString* ns;
    CMPIStatus st = { CMPI_RC_OK, NULL };
    CMPICount count;
    CMPICount i;

    if (!self)
        CMPIRETURN(ERR_FAILED);

    /* Get namespace */

    if (!(ns = CMGetNameSpace(self, &st)))
        return st;

    /* Get classname */

    if (!(cn = CMGetClassName(self, &st)))
        return st;

    /* Print namespace:classname */

    str.append(string_printf("%s:%s\n", CMPIChars(ns), CMPIChars(cn)));
    _indent(str, indent++);
    str.append("{\n");

    /* Print properties */

    count = CMGetKeyCount(self, &st);

    if (!CMPIOKAY(st))
        return st;

    for (i = 0; i < count; i++)
    {
        CMPIData cd;
        CMPIString* pn = NULL;

        /* Get i-th property */

        cd = CMGetKeyAt(self, i, &pn, &st);

        if (!CMPIOKAY(st))
            return st;

        if (!pn)
            CMPIRETURN(ERR_FAILED);

        /* Print property name */

        _indent(str, indent);
        str.append(string_printf("%s=", CMPIChars(pn)));

        /* Print property value */
        _print_value(str,&cd, indent);

        str.append("\n");
    }

    _indent(str, --indent);
    str.append("}\n");

    CMPIRETURN(OK);
}

// output formatted CMPIObjectPath to File
CMPIStatus printCMPIInstance(
    FILE* os,
    const CMPIInstance* self,
    size_t indent )
{
    String str = "";
    CMPIStatus st =  printCMPIInstance(
        str, self, indent);
    fprintf(os, "%s", str.c_str());

    return st;
}

// output formatted CMPIObjectPath to stdout
CMPIStatus printCMPIInstance(
    const CMPIInstance* self,
    size_t indent )
{
    String str = "";
    CMPIStatus st =  printCMPIInstance(
        str, self, indent);
    printf("%s", str.c_str());

    return st;
}

// output formatted CMPIObjectPath to log
CMPIStatus logCMPIInstance(
    const char* file, int line,
    const CMPIInstance* self)
{
    size_t indent = 0;
    String str = "";
    CMPIStatus st =  printCMPIInstance(
        str, self, indent);

    log(LL_DBG, file, line, "CMPIInstance: %s", str.c_str());

    return st;
}

// generate formatted out of CMPI Instance in str
CMPIStatus printCMPIInstance(
    String& str,
    const CMPIInstance* self, 
    size_t indent)
{
    CMPIObjectPath* cop;
    CMPIString* cn;
    CMPIString* ns;
    CMPIStatus st = { CMPI_RC_OK, NULL };
    CMPICount count;
    CMPICount i;

    if (!self)
        CMPIRETURN(ERR_FAILED);

    /* Get object path */

    if (!(cop = CMGetObjectPath(self, &st)))
        return st;

    /* Get namespace */

    if (!(ns = CMGetNameSpace(cop, &st)))
    {
        /* Ignore */
    }

    /* Get classname */

    if (!(cn = CMGetClassName(cop, &st)))
        return st;

    /* Print namespace:classname */
    
    str.append(string_printf("%s:%s\n", CMPIChars(ns), CMPIChars(cn)));
    _indent(str, indent++);
    str.append("{\n");

    /* Print properties */

    count = CMGetPropertyCount(self, &st);

    if (!CMPIOKAY(st))
        return st;

    for (i = 0; i < count; i++)
    {
        CMPIData cd;
        CMPIString* pn = NULL;

        /* Get i-th property */

        cd = CMGetPropertyAt(self, i, &pn, &st);

        if (!CMPIOKAY(st))
            return st;

        if (!pn)
            CMPIRETURN(ERR_FAILED);

        /* Print property name */

        _indent(str, indent);
        str.append(string_printf("%s=", CMPIChars(pn)));

        /* Print property value */

        _print_value(str, &cd, indent);

        //if (cd.type != CMPI_ref || cd.state & CMPI_nullValue)
        if (cd.type != CMPI_ref || CMIsNullValue(cd))
            str.append("\n");
    }


    _indent(str, --indent);
    str.append("}\n");

    CMPIRETURN(OK);
}


CIMPLE_NAMESPACE_END
