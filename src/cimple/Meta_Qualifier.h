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

#ifndef _cimple_Meta_Qualifier_h
#define _cimple_Meta_Qualifier_h

#include "config.h"
#include "Atomic.h"
#include "Meta_Value.h"

CIMPLE_NAMESPACE_BEGIN

struct Meta_Qualifier
{
    Atomic refs;
    const char* name;
    uint8 type;
    uint8 subscript;
    uint16 flavors;
    const Meta_Value* value;
};

// Meta_Class, Meta_Property, and Meta_Reference can be casted to and treated
// as a Meta_Qualified_Object, since they share the same initial fields.
struct Meta_Qualified_Object
{
    Atomic refs;
    uint32 flags;
    const char* name;
    const Meta_Qualifier* const* meta_qualifiers;
    size_t num_meta_qualifiers;
};

CIMPLE_CIMPLE_LINKAGE
void print(const Meta_Qualifier* mq, bool& first);

CIMPLE_CIMPLE_LINKAGE
void print(
    const Meta_Qualifier* const* meta_qualifiers,
    size_t num_meta_qualifiers,
    uint32 flags,
    bool param,
    size_t level);

CIMPLE_CIMPLE_LINKAGE
Meta_Qualifier* clone(const Meta_Qualifier* x);

CIMPLE_CIMPLE_LINKAGE
Meta_Qualifier** clone(
    const Meta_Qualifier* const* meta_qualifiers,
    size_t num_meta_qualifiers);

CIMPLE_CIMPLE_LINKAGE
void destroy(Meta_Qualifier* x);

CIMPLE_CIMPLE_LINKAGE
const Meta_Qualifier* find(
    const Meta_Qualifier* const* meta_qualifiers, 
    size_t num_meta_qualifiers,
    const char* name);

CIMPLE_CIMPLE_LINKAGE
void append(
    const Meta_Qualifier* const*& meta_qualifiers,
    size_t& num_meta_qualifiers,
    const Meta_Qualifier* meta_qualifier);

CIMPLE_CIMPLE_LINKAGE
void filter_qualifiers(
    Meta_Qualified_Object* mqo,
    const char* const* names,
    size_t num_names);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Qualifier_h */
