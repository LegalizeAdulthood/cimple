/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
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

/*
    Functions to display Pegasus CIMInstances.
*/

#include <cassert>
#include "pegasus.h"
#include "Str.h"
#include "print.h"

using namespace Pegasus;

CIMPLE_NAMESPACE_BEGIN
static const char* _typeStrings[] =
{
    "boolean",
    "uint8",
    "sint8",
    "uint16",
    "sint16",
    "uint32",
    "sint32",
    "uint64",
    "sint64",
    "real32",
    "real64",
    "char16",
    "string",
    "datetime",
    "reference",
    "object",
    "instance"
};

static void format_scalar(String& str,
             const CIMValue& v, size_t indent)
{
    if (v.isNull())
    {
        str.append("NULL");
    }
    else
    {
        switch (v.getType())
        {
            case CIMTYPE_BOOLEAN:
            {
                Boolean x;
                v.get(x);
                string_append_printf(str,"%s", (x? "true" : "false"));
                break;
            }
    
            case CIMTYPE_UINT8:
            {
                Uint8 x;
                v.get(x);
                string_append_printf(str,"%d", x);
                break;
            }
    
            case CIMTYPE_SINT8:
            {
                Sint8 x;
                v.get(x);
                string_append_printf(str,"%u", x);
                break;
            }
    
            case CIMTYPE_UINT16:
            {
                Uint16 x;
                v.get(x);
                string_append_printf(str,"%d", x);
                break;
            }
    
            case CIMTYPE_SINT16:
            {
                Sint16 x;
                v.get(x);
                string_append_printf(str,"%u", x);
                break;
            }
    
            case CIMTYPE_UINT32:
            {
                Uint32 x;
                v.get(x);
                string_append_printf(str,"%d", x);
                break;
            }
    
            case CIMTYPE_SINT32:
            {
                Sint32 x;
                v.get(x);
                string_append_printf(str,"%u", x);
                break;
            }
    
            case CIMTYPE_UINT64:
            {
                Uint64 x;
                v.get(x);
                string_append_printf(str,CIMPLE_LLU, x);
                break;
            }
    
            case CIMTYPE_SINT64:
            {
                Sint64 x;
                v.get(x);
                string_append_printf(str,CIMPLE_LLD, x);
                break;
            }
    
            case CIMTYPE_REAL32:
            {
                Real32 x;
                v.get(x);
                string_append_printf(str,"%f", x);
                break;
            }
    
            case CIMTYPE_REAL64:
            {
                Real64 x;
                v.get(x);
                string_append_printf(str,"%lf", x);
                break;
            }
    
            case CIMTYPE_CHAR16:
            {
                Char16 x;
                v.get(x);
                string_append_printf(str,"%d", Uint32(x));
                break;
            }
    
            case CIMTYPE_STRING:
            {
                Pegasus::String x;
                v.get(x);
                string_append_printf(str,"\"%s\"", *Str(x));
                break;
            }
    
            case CIMTYPE_DATETIME:
            {
                CIMDateTime x;
                v.get(x);
                string_append_printf(str,"%s", *Str(x.toString()));
                break;
            }
    
            case CIMTYPE_REFERENCE:
            {
                CIMObjectPath x;
                v.get(x);
                string_append_printf(str,"%s", *Str(x.toString()));
                break;
            }
    
            case CIMTYPE_OBJECT:
            {
                CIMObject x;
                v.get(x);
    
                if (x.isInstance())
                {
                    formatToString(str, CIMInstance(x), indent);
                }
                // Following should never occur in the adapter and
                // since our support for clients is limited we will simply
                // output indicator that this is a class.
                else
                {
                    str.append("<CLASS>");
                }
                break;
            }
    
#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
    
            case CIMTYPE_INSTANCE:
            {
                CIMInstance x;
                v.get(x);
                formatToString(str, x, indent);
                break;
            }
    
#endif /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */
    
            default:
                printf("Error: Scalar type %u not defined\n",
                       v.getType() );
                break;
        }
    }
}

// Set separator character if not first item in list
void _set_separator(String& str, size_t i)
{
    if (i != 0)
        str.append(", ");
}

// Template for processing arrays of each data type. Gets array and
// loops to process scalar values
template<class T>
static void format_array_aux(
    String & str,
    const CIMValue& v, 
    T* tag,
    size_t& indent)
{
    Pegasus::Array<T> x;
    v.get(x);

    for (size_t i = 0; i < x.size(); i++)
    {
        _set_separator(str, i);

        format_scalar(str, CIMValue(x[i]), indent);
    }
}

static void format_array(String& str,
    const CIMValue& v,
    size_t& indent)
{
    str.append("{ ");
    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
            format_array_aux(str, v, (Boolean*)0, indent);
            break;

        case CIMTYPE_UINT8:
            format_array_aux(str, v, (Uint8*)0, indent);
            break;

        case CIMTYPE_SINT8:
            format_array_aux(str, v, (Sint8*)0, indent);
            break;

        case CIMTYPE_UINT16:
            format_array_aux(str, v, (Uint16*)0, indent);
            break;

        case CIMTYPE_SINT16:
            format_array_aux(str, v, (Sint16*)0, indent);
            break;

        case CIMTYPE_UINT32:
            format_array_aux(str, v, (Uint32*)0, indent);
            break;

        case CIMTYPE_SINT32:
            format_array_aux(str, v, (Sint32*)0, indent);
            break;

        case CIMTYPE_UINT64:
            format_array_aux(str, v, (Uint64*)0, indent);
            break;

        case CIMTYPE_SINT64:
            format_array_aux(str, v, (Sint64*)0, indent);
            break;

        case CIMTYPE_REAL32:
            format_array_aux(str, v, (Real32*)0, indent);
            break;

        case CIMTYPE_REAL64:
            format_array_aux(str, v, (Real64*)0, indent);
            break;

        case CIMTYPE_CHAR16:
            format_array_aux(str, v, (Char16*)0, indent);
            break;

        case CIMTYPE_STRING:
            format_array_aux(str, v, (Pegasus::String*)0, indent);
            break;

        case CIMTYPE_DATETIME:
            format_array_aux(str, v, (CIMDateTime*)0, indent);
            break;

        case CIMTYPE_REFERENCE:
            format_array_aux(str, v, (CIMObjectPath*)0, indent);
            break;

        case CIMTYPE_OBJECT:
            format_array_aux(str, v, (CIMObject*)0, indent);
            break;

#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES
        case CIMTYPE_INSTANCE:
            format_array_aux(str, v, (CIMInstance*)0, indent);
            break;
#endif
        default:
            printf("Error: Array. Type %u not defined\n",v.getType());
            break;
    }
    str.append(" }");
}

// Print name and value indented and on single line
void format_property(String& str, CIMConstProperty cp, size_t& indent_level)
{
    CIMValue v = cp.getValue();

    // Display property name, type and array indicator
    istring_printf(str, indent_level, "%s %s%s = ",
        _typeStrings[v.getType()],
        *Str(cp.getName()),
        (v.isArray()? "[]" : ""));

    if (v.isArray())
        format_array(str, v, indent_level);
    else
        format_scalar(str, v, indent_level);

    str.append("\n");
}

// put the formatted definition of the instance into a String. The indent
// level is an internal function to provide indenting of embedded entities
void formatToString(String& str,
                    const CIMConstInstance& ci,
                    size_t indent_level)
{
    if (ci.isUninitialized())
    {
        str.append("Unitialized Instance\n");
    }
    else
    {
        string_append_printf(str, "instance of %s\n", *Str(ci.getClassName()));
        
        istring_printf(str, indent_level++, "{\n");

        for (Uint32 i = 0; i < ci.getPropertyCount(); i++)
        {
            CIMConstProperty cp = ci.getProperty(i);
            format_property(str, cp, indent_level);
        }
    
        istring_printf(str, --indent_level, "%s", "}");
    }
}

/**
 * print a CIM Instance to standard output formatted roughly as mof is 
 * formatted. 
 * @param ci CIMInstance (Pegasus C++ object format) of instance
 */
void print(const CIMConstInstance& ci)
{
    String str;
    size_t indent_level = 0;
    formatToString(str, ci, indent_level);
    printf("%s\n", str.c_str());
}

/**
 * Output a formated display of a Pegasus CIMInstance to the CIMPLE log 
 * file. This function is intended to be used by the CIMPLE pegasus adapter 
 * and should be used through a macro call so that it can be completely 
 * disabled when not required. 
 * 
 * @param ci Instance to be displayed
 * @param lvl  Log level
 * @param file Code Source Line (__FILE__)
 * @param line Code source line (__LINE__)
 */
void logPegasusInstance(const CIMConstInstance& ci,
                        const Log_Level lvl,
                        const char* file,
                        int line)
{
    String str;
    formatToString(str, ci, 0);
    log(LL_DBG, file, line, "PegasusInstance: %s", str.c_str());
}

CIMPLE_NAMESPACE_END
