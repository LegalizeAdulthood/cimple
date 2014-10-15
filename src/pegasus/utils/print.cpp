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

#include <cassert>
#include "pegasus.h"
#include "Str.h"
#include "print.h"

using namespace Pegasus;

CIMPLE_NAMESPACE_BEGIN

static void print_scalar(const Pegasus::String& name, const CIMValue& v)
{
    if (v.isNull())
    {
        printf("NULL");
        return;
    }

    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
        {
            Boolean x;
            v.get(x);
            if (x)
                printf("true");
            else
                printf("false");
            break;
        }

        case CIMTYPE_UINT8:
        {
            Uint8 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT8:
        {
            Sint8 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT16:
        {
            Uint16 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT16:
        {
            Sint16 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT32:
        {
            Uint32 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT32:
        {
            Sint32 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT64:
        {
            Uint64 x;
            v.get(x);
            printf(CIMPLE_LLU, x);
            break;
        }

        case CIMTYPE_SINT64:
        {
            Sint64 x;
            v.get(x);
            printf(CIMPLE_LLD, x);
            break;
        }

        case CIMTYPE_REAL32:
        {
            Real32 x;
            v.get(x);
            printf("%f", x);
            break;
        }

        case CIMTYPE_REAL64:
        {
            Real64 x;
            v.get(x);
            printf("%lf", x);
            break;
        }

        case CIMTYPE_CHAR16:
        {
            Char16 x;
            v.get(x);
            printf("%d", Uint32(x));
            break;
        }

        case CIMTYPE_STRING:
        {
            Pegasus::String x;
            v.get(x);
            printf("%s", *Str(x));
            break;
        }

        case CIMTYPE_DATETIME:
        {
            CIMDateTime x;
            v.get(x);
            printf("%s", *Str(x.toString()));
            break;
        }

        case CIMTYPE_REFERENCE:
        {
            CIMObjectPath x;
            v.get(x);
            printf("%s", *Str(x.toString()));
            break;
        }

        case CIMTYPE_OBJECT:
        {
            CIMObject x;
            v.get(x);

            if (x.isInstance())
            {
                print(CIMInstance(x), true);
            }
            else
            {
                printf("<CLASS>");
            }
            break;
        }

#ifdef CIMPLE_ENABLE_EMBEDDED_INSTANCES

        case CIMTYPE_INSTANCE:
        {
            CIMInstance x;
            v.get(x);

            print(x, true);
        }

#endif /* CIMPLE_ENABLE_EMBEDDED_INSTANCES */

        default:
            break;
    }
}

template<class T>
static void print_array_aux(
    const Pegasus::String& name, 
    const CIMValue& v, 
    T* tag)
{
    Pegasus::Array<T> x;
    v.get(x);

    printf("{");

    for (Uint32 i = 0; i < x.size(); i++)
    {
        print_scalar(name, CIMValue(x[i]));

        if (i + 1 != x.size())
            printf(", ");
    }

    printf("}");
}

static void print_array(const Pegasus::String& name, const CIMValue& v)
{
    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
            print_array_aux(name, v, (Boolean*)0);
            break;

        case CIMTYPE_UINT8:
            print_array_aux(name, v, (Uint8*)0);
            break;

        case CIMTYPE_SINT8:
            print_array_aux(name, v, (Sint8*)0);
            break;

        case CIMTYPE_UINT16:
            print_array_aux(name, v, (Uint16*)0);
            break;

        case CIMTYPE_SINT16:
            print_array_aux(name, v, (Sint16*)0);
            break;

        case CIMTYPE_UINT32:
            print_array_aux(name, v, (Uint32*)0);
            break;

        case CIMTYPE_SINT32:
            print_array_aux(name, v, (Sint32*)0);
            break;

        case CIMTYPE_UINT64:
            print_array_aux(name, v, (Uint64*)0);
            break;

        case CIMTYPE_SINT64:
            print_array_aux(name, v, (Sint64*)0);
            break;

        case CIMTYPE_REAL32:
            print_array_aux(name, v, (Real32*)0);
            break;

        case CIMTYPE_REAL64:
            print_array_aux(name, v, (Real64*)0);
            break;

        case CIMTYPE_CHAR16:
            print_array_aux(name, v, (Char16*)0);
            break;

        case CIMTYPE_STRING:
            print_array_aux(name, v, (Pegasus::String*)0);
            break;

        case CIMTYPE_DATETIME:
            print_array_aux(name, v, (CIMDateTime*)0);
            break;

        case CIMTYPE_REFERENCE:
            print_array_aux(name, v, (CIMObjectPath*)0);
            break;

        default:
            break;
    }
}

static void print_value(const Pegasus::String& name, const CIMValue& v)
{
    printf("%s=", *Str(name));

    if (v.isArray())
        print_array(name, v);
    else
        print_scalar(name, v);

    printf("\n");
}

void print(const CIMConstInstance& ci, bool indent)
{
    char in[5];

    if (indent)
        strcpy(in, "    ");
    else
        strcpy(in, "");

    printf("%sinstance of %s\n", in, *Str(ci.getClassName()));
    printf("%s{\n", in);

    for (Uint32 i = 0; i < ci.getPropertyCount(); i++)
    {
        CIMConstProperty cp = ci.getProperty(i);

        printf("%s    ", in);
        print_value(*Str(cp.getName()), cp.getValue());
    }

    printf("%s}\n", in);
}

CIMPLE_NAMESPACE_END
