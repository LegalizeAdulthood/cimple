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

#include "Reference_Facade.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

Reference_Facade::Reference_Facade()
{
}

Reference_Facade::~Reference_Facade()
{
}

void Reference_Facade::print(FILE* os, size_t level) const
{
    iprintf(os, level, "Reference_Facade\n");
    iprintf(os, level, "{\n");
    level++;

    for (size_t i = 0, n = count(); i < n; i++)
    {
        String name = get_name(i);
        bool null = get_null(i);

        // Handle reference up front!

        if (is_reference(i))
        {
            // ATTN: handle null reference here!

            Reference_Facade* r = get_reference(i);

            iprintf(os, level, "%s ref %s =", 
                r->class_name().c_str(), name.c_str());

            r->print(os, level);

            delete r;
            continue;
        }

        // Handle scalars now.

        Type type = get_type(i);

        iprintf(os, level, "%s %s =", name.c_str(), type_name[int(type)]);

        if (null)
        {
            fprintf(os, " null;\n");
            continue;
        }

        switch (type)
        {
            case BOOLEAN:
            {
                boolean x = get_boolean(i);
                __print_scalar(os, type, &x);
            }

            case UINT8:
            {
                uint8 x = get_uint8(i);
                __print_scalar(os, type, &x);
            }

            case SINT8:
            {
                sint8 x = get_sint8(i);
                __print_scalar(os, type, &x);
            }

            case UINT16:
            {
                uint16 x = get_uint16(i);
                __print_scalar(os, type, &x);
            }

            case SINT16:
            {
                sint16 x = get_sint16(i);
                __print_scalar(os, type, &x);
            }

            case UINT32:
            {
                uint32 x = get_uint32(i);
                __print_scalar(os, type, &x);
            }

            case SINT32:
            {
                sint32 x = get_sint32(i);
                __print_scalar(os, type, &x);
            }

            case UINT64:
            {
                uint64 x = get_uint64(i);
                __print_scalar(os, type, &x);
            }

            case SINT64:
            {
                sint64 x = get_sint64(i);
                __print_scalar(os, type, &x);
            }

            case REAL32:
            {
                real32 x = get_real32(i);
                __print_scalar(os, type, &x);
            }

            case REAL64:
            {
                real64 x = get_real64(i);
                __print_scalar(os, type, &x);
            }

            case CHAR16:
            {
                char16 x = get_char16(i);
                __print_scalar(os, type, &x);
            }

            case STRING:
            {
                String x = get_string(i);
                __print_scalar(os, type, &x);
            }

            case DATETIME:
            {
                Datetime x = get_datetime(i);
                __print_scalar(os, type, &x);
            }

            default:
                break;
        }

        fputc('\n', os);
    }

    level--;
    iprintf(os, level, "}\n");
}

CIMPLE_NAMESPACE_END
