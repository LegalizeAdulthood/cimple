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

#include "Meta_Property.h"
#include "Type.h"
#include "Meta_Feature.h"
#include "Array.h"
#include "Meta_Class.h"
#include "Meta_Value.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

bool property_eq(
    const Meta_Property* mp, 
    const void* value1,
    const void* value2)
{
    if (null_of(mp, value1) != null_of(mp, value2))
        return false;

    if (mp->subscript == 0)
    {
        switch (mp->type)
        {
            case BOOLEAN:
                return *((boolean*)value1) == *((boolean*)value2);

            case UINT8:
            case SINT8:
                return *((uint8*)value1) == *((uint8*)value2);

            case UINT16:
            case SINT16:
            case CHAR16:
                return *((uint16*)value1) == *((uint16*)value2);

            case UINT32:
            case SINT32:
                return *((uint32*)value1) == *((uint32*)value2);

            case UINT64:
            case SINT64:
                return *((uint64*)value1) == *((uint64*)value2);

            case REAL32:
                return *((real32*)value1) == *((real32*)value2);

            case REAL64:
                return *((real64*)value1) == *((real64*)value2);

            case STRING:
                return *((String*)value1) == *((String*)value2);

            case DATETIME:
                return *((Datetime*)value1) == *((Datetime*)value2);
        }
    }
    else
    {
        switch (mp->type)
        {
            case BOOLEAN:
                return *((Array_boolean*)value1) == *((Array_boolean*)value2);

            case UINT8:
            case SINT8:
                return *((Array_uint8*)value1) == *((Array_uint8*)value2);

            case UINT16:
            case SINT16:
            case CHAR16:
                return *((Array_uint16*)value1) == *((Array_uint16*)value2);

            case UINT32:
            case SINT32:
                return *((Array_uint32*)value1) == *((Array_uint32*)value2);

            case UINT64:
            case SINT64:
                return *((Array_uint64*)value1) == *((Array_uint64*)value2);

            case REAL32:
                return *((Array_real32*)value1) == *((Array_real32*)value2);

            case REAL64:
                return *((Array_real64*)value1) == *((Array_real64*)value2);

            case STRING:
                return *((Array_String*)value1) == *((Array_String*)value2);

            case DATETIME:
                return *((Array_Datetime*)value1) == *((Array_Datetime*)value2);
        }
    }

    // Unreachable!
    return true;
}

void destroy(Meta_Property* mp)
{
    // Meta_Property.name:
    free((char*)(mp->name));

    // Meta_Property.meta_qualifiers:

    for (size_t i = 0; i < mp->num_meta_qualifiers; i++)
        destroy((Meta_Qualifier*)mp->meta_qualifiers[i]);

    free((Meta_Qualifier*)mp->meta_qualifiers);

    // Meta_Property.value:
    destroy((Meta_Value*)mp->value, Type(mp->type), mp->subscript != 0);

    // Meta_Property:
    free(mp);
}

Meta_Property* clone(const Meta_Property* x, bool clone_value)
{
    // ATTN: impement reference counting on this and other types.
    // ATTN: avoid copy when x.refs == 0.
    Meta_Property* mp = (Meta_Property*)calloc(1, sizeof(Meta_Property));
    memcpy(mp, x, sizeof(Meta_Property));
    mp->name = strdup(x->name);

    if (clone_value)
        mp->value = clone(x->value, Type(x->type), x->subscript != 0);

    return mp;
}

//==============================================================================
//
// print()
//
//==============================================================================

void print(const Meta_Property* mp, bool is_parameter)
{
    printf("%s %s", type_name[mp->type], mp->name);

    if (mp->subscript == -1)
        printf("[]");
    else if (mp->subscript != 0)
        printf("[%d]", mp->subscript);

    if (!is_parameter)
    {
        printf(" = ");
        print(mp->value, Type(mp->type), mp->subscript != 0);
    }
}

Meta_Property* create_meta_property(
    const char* name, 
    Type type, 
    sint32 subscript, 
    uint32 offset,
    bool key)
{
    // Meta_Property.refs
    // Meta_Property.flags
    // Meta_Property.name
    // Meta_Property.meta_qualifiers*
    // Meta_Property.num_meta_qualifiers*
    // Meta_Property.type
    // Meta_Property.subscript
    // Meta_Property.offset
    // Meta_Property.value*
    //
    // *no initialized here.

    Meta_Property* mp = CIMPLE_CALLOC(Meta_Property);

    // ATTN: implement reference counting.
    // Atomic_create(&mp->refs, 1);

    mp->flags = CIMPLE_FLAG_PROPERTY | CIMPLE_FLAG_READ;

    if (key)
        mp->flags |= CIMPLE_FLAG_KEY;

    *((char**)&mp->name) = strdup(name);

    mp->type = type;
    mp->subscript = subscript;
    mp->offset = offset;

    return mp;
}

CIMPLE_NAMESPACE_END

