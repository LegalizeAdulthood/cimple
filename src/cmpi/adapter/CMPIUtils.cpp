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

//#define KSTATUS_INIT { CMPI_RC_OK, NULL }
#define CMPIRETURN(CODE) return __KReturn(CMPI_RC_##CODE)
static void __KSetStatus(CMPIStatus* status, CMPIrc rc)
{
    if (status)
    {
        status->rc = rc;
        status->msg = NULL;
    }
}

static CMPIStatus __KReturn(CMPIrc RC)
{
    CMPIStatus status;
    __KSetStatus(&status, RC);
    return status;
}

static void _indent(FILE* os, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
        fprintf(os, "    ");
}

static void _print_scalar(
    FILE* os,
    const CMPIData* cd, 
    size_t n)
{
    if (cd->state & CMPI_nullValue)
    //if (CMIsNullValue(cd))
    {
        fprintf(os, "null");
        return;
    }

    switch (cd->type & ~CMPI_ARRAY)
    {
        case CMPI_boolean:
            fprintf(os, "%s", cd->value.boolean ? "true" : "false");
            break;
        case CMPI_uint8:
            fprintf(os, "%u", cd->value.uint8);
            break;
        case CMPI_sint8:
            fprintf(os, "%d", cd->value.sint8);
            break;
        case CMPI_uint16:
            fprintf(os, "%u", cd->value.uint16);
            break;
        case CMPI_sint16:
            fprintf(os, "%d", cd->value.sint16);
            break;
        case CMPI_uint32:
            fprintf(os, "%u", cd->value.uint32);
            break;
        case CMPI_sint32:
            fprintf(os, "%d", cd->value.sint32);
            break;
        case CMPI_uint64:
            fprintf(os, "%llu", cd->value.uint64);
            break;
        case CMPI_sint64:
            fprintf(os, "%lld", cd->value.sint64);
            break;
        case CMPI_real32:
            fprintf(os, "%f", cd->value.real32);
            break;
        case CMPI_real64:
            fprintf(os, "%f", cd->value.real64);
            break;
        case CMPI_char16:
            fprintf(os, "%u", cd->value.char16);
            break;
        case CMPI_string:
            /* ATTN: improve string formatting */
            fprintf(os, "\"%s\"", CMPIChars(cd->value.string));
            break;
        case CMPI_dateTime:
            fprintf(os, "%s", 
                CMPIChars(CMGetStringFormat(cd->value.dateTime, NULL)));
            break;
        case CMPI_ref:
            printCMPIObjectPath(os, cd->value.ref, n);
            break;
        case CMPI_instance:
            printCMPIInstance(os, cd->value.inst, n);
            break;
    }
}

static void _print_array(FILE* os, const CMPIData* cd, size_t n)
{
    CMPICount count;
    CMPIArray* array;
    CMPICount i;

    if (cd->state & CMPI_nullValue)
    //if (CMIsNullValue(cd))
    {
        fprintf(os, "null");
        return;
    }

    if (!(array = cd->value.array))
        return;

    fprintf(os, "{");

    count = CMGetArrayCount(array, NULL);

    for (i = 0; i < count; i++)
    {
        CMPIStatus st = { CMPI_RC_OK, NULL };
        CMPIData cd = CMGetArrayElementAt(array, i, &st);

        if (CMPIOKAY(st))
        {
            _print_scalar(os, &cd, n);

            if (i + 1 != count)
                fprintf(os, ", ");
        }
    }

    fprintf(os, "}");
}

CMPIStatus printCMPIObjectPath(
    FILE* os,
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

    /* Print namesapce:classname */

    fprintf(os, "%s:%s\n", CMPIChars(ns), CMPIChars(cn));
    _indent(os, indent);
    fprintf(os, "{\n");
    indent++;

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

        _indent(os, indent);
        fprintf(os, "%s=", CMPIChars(pn));

        /* Print property value */

        if (cd.type & CMPI_ARRAY)
            _print_array(os, &cd, indent);
        else
            _print_scalar(os, &cd, indent);

        fprintf(os, "\n");
    }

    indent--;
    _indent(os, indent);
    fprintf(os, "}\n");

    CMPIRETURN(OK);
}

CMPIStatus printCMPIInstance(
    FILE* os,
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

    fprintf(os, "%s:%s\n", CMPIChars(ns), CMPIChars(cn));
    _indent(os, indent);
    fprintf(os, "{\n");
    indent++;

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

        _indent(os, indent);
        fprintf(os, "%s=", CMPIChars(pn));

        /* Print property value */

        if (cd.type & CMPI_ARRAY)
            _print_array(os, &cd, indent);
        else
            _print_scalar(os, &cd, indent);

        //if (cd.type != CMPI_ref || cd.state & CMPI_nullValue)
        if (cd.type != CMPI_ref || CMIsNullValue(cd))
            fprintf(os, "\n");
    }

    indent--;
    _indent(os, indent);
    fprintf(os, "}\n");

    CMPIRETURN(OK);
}

CIMPLE_NAMESPACE_END
