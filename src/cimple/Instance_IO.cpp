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

#include <cstdarg>
#include "Instance.h"

CIMPLE_NAMESPACE_BEGIN

struct IO
{
    static void _print_scalar(uint32 type, const void* ptr)
    {
        switch (Type(type))
        {
            case BOOLEAN:
            {
                printf(*((boolean*)ptr) ?  "true" : "false");
                break;
            }

            case UINT8:
            {
                printf("%u", *((uint8*)ptr));
                break;
            }

            case SINT8:
            {
                printf("%d", *((sint8*)ptr));
                break;
            }

            case UINT16:
            {
                printf("%u", *((uint16*)ptr));
                break;
            }

            case SINT16:
            {
                printf("%d", *((sint16*)ptr));
                break;
            }

            case UINT32:
            {
                printf("%u", *((uint32*)ptr));
                break;
            }

            case SINT32:
            {
                printf("%d", *((sint32*)ptr));
                break;
            }

            case UINT64:
            {
                printf(CIMPLE_LLU, *((uint64*)ptr));
                break;
            }

            case SINT64:
            {
                printf(CIMPLE_LLD, *((sint64*)ptr));
                break;
            }

            case REAL32:
            {
                printf("%f", *((real32*)ptr));
                break;
            }

            case REAL64:
            {
                printf("%f", *((real64*)ptr));
                break;
            }

            case CHAR16:
            {
                uint16 c = *((uint16*)ptr);

                if (c >= ' ' && c <= '~')
                    printf("'%c'", c);
                else
                    printf("0x%04X", c);
                break;
            }

            case DATETIME:
            {
                char buffer[32];
                ((Datetime*)ptr)->ascii(buffer);
                printf("%s", buffer);
                break;
            }

            case STRING:
            {
                printf("\"%s\"", ((String*)ptr)->c_str());
                break;
            }
        }
    }

    static void _print_array(uint32 type, const void* ptr, size_t depth)
    {
        printf("{ ");

        Array_Base* base = (Array_Base*)ptr;
        const char* data = base->_rep->data;
        size_t size = base->_rep->size;

        for (size_t i = 0; i < size; i++)
        {
            _print_scalar(type, data);

            if (i + 1 != size)
                putchar(',');

            putchar(' ');
            data += type_size[type];
        }

        printf("}");
    }

    // Indented printf().
    static int iprintf(size_t level, const char* format, ...)
    {
        printf("%*s", int(level * 4), "");

        va_list ap;
        va_start(ap, format);
        int r = vprintf(format, ap);
        va_end(ap);

        return r;
    }

    static void _print_property(
        const Meta_Property* mp, const void* prop, size_t level)
    {
        iprintf(level, "%s %s", type_name[mp->type], mp->name);

        if (mp->subscript)
            printf("[]");

        printf(" = ");

        if (null_of(mp, prop))
            printf("null");
        else if (mp->subscript == 0)
            _print_scalar(mp->type, prop);
        else
            _print_array(mp->type, prop, 0);

        printf(";\n");
    }

    static void _print_aux(
        const Instance* inst, const char* name, size_t level, bool keys_only)
    {
        CIMPLE_ASSERT(inst != 0);
        CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

        const Meta_Class* mc = inst->meta_class;

        if (name)
            iprintf(level, "%s %s =\n", inst->meta_class->name, name);
        else
            iprintf(level, "%s \n", inst->meta_class->name);

        iprintf(level, "{\n");

        for (size_t i = 0; i < mc->num_meta_features; i++)
        {
            uint32 flags = mc->meta_features[i]->flags;

            if (keys_only && !(flags & CIMPLE_FLAG_KEY))
                continue;

            // Skip non-keys if we are not at the top level.

            if (!(level == 0 || 
                (flags & CIMPLE_FLAG_KEY) || 
                (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)))
            {
                continue;
            }

            level++;

            if (flags & CIMPLE_FLAG_PROPERTY)
            {
                const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
                const void* prop = property_of(inst, mp);
                _print_property(mp, prop, level);
            }
            else if (flags & CIMPLE_FLAG_REFERENCE)
            {
                const Meta_Reference* mr = 
                    (Meta_Reference*)mc->meta_features[i];
                Instance* tmp = *((Instance**)((uint8*)inst + mr->offset));

                if (tmp)
                    _print_aux(tmp, mr->name, level, keys_only);
                else
                    iprintf(level, "%s %s = null;\n", 
                        mr->meta_class->name, mr->name);
            }

            level--;
        }

        iprintf(level, "}\n");
    }
};

void print(const Instance* inst, bool keys_only)
{
    IO::_print_aux(inst, 0, 0, keys_only);
}

CIMPLE_NAMESPACE_END
