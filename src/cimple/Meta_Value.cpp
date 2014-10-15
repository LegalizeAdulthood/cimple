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

#include "Meta_Value.h"

CIMPLE_NAMESPACE_BEGIN

void print(const Meta_Value* x, Type type, bool array)
{
    if (!x)
    {
        printf("NULL");
        return;
    }

    if (array)
    {
        Meta_Value_Array<void>* px = (Meta_Value_Array<void>*)x;
        printf("{");
        print_array(type, px->elements, px->num_elements);
        printf("}");
    }
    else
    {
        print_scalar(type, x);
    }
}

Meta_Value* clone(const Meta_Value* x, Type type, bool array)
{
    if (!x)
        return 0;

    size_t value_size = literal_type_size[type];

    if (array)
    {
        Meta_Value_Array<void>* px = (Meta_Value_Array<void>*)(x);
        Meta_Value_Array<void>* mv = 
            (Meta_Value_Array<void>*)malloc(sizeof(Meta_Value_Array<void>));

        mv->num_elements = px->num_elements;
        mv->elements = malloc(px->num_elements * value_size);

        switch (type)
        {
            case BOOLEAN:
            case UINT8:
            case SINT8:
            case UINT16:
            case SINT16:
            case UINT32:
            case SINT32:
            case UINT64:
            case SINT64:
            case REAL32:
            case REAL64:
            case CHAR16:
            {
                memcpy((void*)mv->elements, 
                    px->elements, px->num_elements * value_size);
                break;
            }

            case STRING:
            case DATETIME:
            {
                char** p = (char**)px->elements;
                char** q = (char**)mv->elements;

                for (size_t i = 0; i < px->num_elements; i++)
                    q[i] = strdup(p[i]);

                break;
            }
        }

        return (Meta_Value*)mv;
    }
    else
    {
        Meta_Value* mv = (Meta_Value*)malloc(value_size);

        switch (type)
        {
            case BOOLEAN:
            case UINT8:
            case SINT8:
            case UINT16:
            case SINT16:
            case UINT32:
            case SINT32:
            case UINT64:
            case SINT64:
            case REAL32:
            case REAL64:
            case CHAR16:
                memcpy(mv, x, value_size);
                break;

            case STRING:
            case DATETIME:
                *((char**)mv) = strdup(*((char**)x));
                break;
        }

        return mv;
    }
}

void destroy(Meta_Value* x, Type type, bool array)
{
    if (!x)
        return;

    // Meta_Qualifier.value:

    if (array)
    {
        Meta_Value_Array<void>* px = (Meta_Value_Array<void>*)(x);

        switch (type)
        {
            case BOOLEAN:
            case UINT8:
            case SINT8:
            case UINT16:
            case SINT16:
            case UINT32:
            case SINT32:
            case UINT64:
            case SINT64:
            case REAL32:
            case REAL64:
            case CHAR16:
                free((void*)px->elements);
                break;

            case STRING:
            case DATETIME:
            {
                char** p = (char**)((Meta_Value_Array<char*>*)x)->elements;

                for (size_t i = 0; i < px->num_elements; i++)
                    free(p[i]);

                free(p);

                break;
            }
        }
    }
    else
    {
        switch (type)
        {
            case BOOLEAN:
            case UINT8:
            case SINT8:
            case UINT16:
            case SINT16:
            case UINT32:
            case SINT32:
            case UINT64:
            case SINT64:
            case REAL32:
            case REAL64:
            case CHAR16:
                // Nothing to free.
                break;

            case STRING:
            case DATETIME:
                free(((Meta_Value_Scalar<char*>*)x)->value);
                break;
        }
    }

    free(x);
}

CIMPLE_NAMESPACE_END

