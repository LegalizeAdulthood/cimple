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

#ifndef _cimple_Meta_Property_h
#define _cimple_Meta_Property_h

#include "config.h"
#include "Type.h"
#include "Meta_Feature.h"
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

/** This structure defines meta-data for a CIM class property. It shares first 
    two fields with the Meta_Feature structure, which functions as a base type.
    That is, Meta_Property pointer can be cast to a Meta_Feature pointer.
*/
struct Meta_Property
{
    /* Meta_Feature fields */
    uint32 flags;
    const char* name;

    /* Local fields */
    uint16 type;
    sint16 subscript;
    uint32 offset;
};

/** Returns the size of the property type (excluding the null flag)
*/
inline size_t type_size_of(const Meta_Property* mp)
{
    return mp->subscript ? sizeof(Array_Base) : type_size[mp->type];
}

/** Returns the null flag of the given property.
*/
inline uint8& null_of(const Meta_Property* mp, const void* prop)
{
    return *((uint8*)prop + type_size_of(mp));
}

bool property_eq(const Meta_Property* mp, const void* prop1, const void* prop2);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Property_h */
