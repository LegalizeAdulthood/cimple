/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

#include "Converter.h"

using namespace cimple;

#ifdef CIMPLE_NEED_CMPI_IO

static const char* type_name_of(CMPIType type)
{
    switch(type & ~CMPI_ARRAY)
    {
        case CMPI_boolean:
            return "boolean";
        case CMPI_uint8:
            return "uint8";
        case CMPI_sint8:
            return "sint8";
        case CMPI_uint16:
            return "uint16";
        case CMPI_sint16:
            return "sint16";
        case CMPI_uint32:
            return "uint32";
        case CMPI_sint32:
            return "sint32";
        case CMPI_uint64:
            return "uint64";
        case CMPI_sint64:
            return "sint64";
        case CMPI_real32:
            return "real32";
        case CMPI_real64:
            return "real64";
        case CMPI_char16:
            return "char16";
        case CMPI_string:
            return "string";
        case CMPI_dateTime:
            return "datetime";
        case CMPI_ref:
            return "ref";
        default:
            printf("[%d]\n", type);
            assert(0);
    }

    return "<unknown>";
}

void print_scalar(const CMPIData& data)
{
    switch(data.type)
    {
        case CMPI_boolean:
            printf("\"%s\"", data.value.boolean ? "true" : "false");
            break;

        case CMPI_uint8:
            printf("%u", data.value.uint8);
            break;

        case CMPI_sint8:
            printf("%d", data.value.sint8);
            break;

        case CMPI_uint16:
            printf("%u", data.value.uint16);
            break;

        case CMPI_sint16:
            printf("%d", data.value.sint16);
            break;

        case CMPI_uint32:
            printf("%u", data.value.uint32);
            break;

        case CMPI_sint32:
            printf("%d", data.value.sint32);
            break;

        case CMPI_uint64:
            printf("%llu", data.value.uint64);
            break;

        case CMPI_sint64:
            printf("%lld", data.value.sint64);
            break;

        case CMPI_real32:
            printf("%f", data.value.real32);
            break;

        case CMPI_real64:
            printf("%lf", data.value.real64);
            break;

        case CMPI_char16:
            printf("%u", data.value.char16);
            break;

        case CMPI_string:
            printf("%s", CMGetCharPtr(data.value.string));
            break;

        case CMPI_dateTime:
        {
            CMPIString* tmp = CMGetStringFormat(data.value.dateTime, NULL);
            printf("%s", CMGetCharPtr(tmp));
            break;
        }

        case CMPI_ref:
        {
            print(data.value.ref);
            break;
        }

        default:
            assert(0);
            break;
    }
}

void print(const CMPIData& data)
{
    if (data.state & CMPI_nullValue)
    {
        printf("null");
        return;
    }

    if (CMIsArray(data))
    {
        printf("{");

        CMPICount n = CMGetArrayCount(data.value.array, NULL);

        for (CMPICount i = 0; i < n; i++)
        {
            CMPIData td = CMGetArrayElementAt(data.value.array, i, NULL);
            print_scalar(td);

            if (i + 1 != n)
                printf(",");
        }

        printf("}");
    }
    else
        print_scalar(data);
}

void print(const CMPIObjectPath* op)
{
    printf("CMPIObjectPath\n");
    printf("{\n");

    printf("    name_space: \"%s\"\n", name_space(op));
    printf("    class_name: \"%s\"\n", class_name(op));
    printf("    host_name: \"%s\"\n", host_name(op));
    printf("    ---\n");

    for (size_t i = 0, n = CMGetKeyCount(op, NULL); i < n; i++)
    {
        CMPIString* name;
        CMPIData data = CMGetKeyAt(op, i, &name, NULL);

        printf("    %s(%s): ", CMGetCharPtr(name), type_name_of(data.type));
        print(data);
        putchar('\n');
    }

    printf("}\n");
}

void print(const CMPIInstance* inst)
{
    printf("CMPIInstance\n");
    printf("{\n");

    for (size_t i = 0, n = CMGetPropertyCount(inst, NULL); i < n; i++)
    {
        CMPIString* name;
        CMPIData data = CMGetPropertyAt(inst, i, &name, NULL);

        if (data.type == 0)
        {
            // FIXME: for some reason the data type is zero here. Embedded
            // object types are not converted correctly here.
            continue;
        }

        printf("    %s(%s): ", CMGetCharPtr(name), type_name_of(data.type));
        print(data);
        putchar('\n');
    }

    printf("}\n");
}

#endif /* CIMPLE_NEED_CMPI_IO */
