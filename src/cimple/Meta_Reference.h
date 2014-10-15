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

#ifndef _cimple_Meta_Reference_h
#define _cimple_Meta_Reference_h

#include "config.h"
#include "Meta_Feature.h"

CIMPLE_NAMESPACE_BEGIN

struct Meta_Class;

// This structure defines meta-data for a CIM class reference. It shares first 
// two fields with the Meta_Feature structure, which functions as a base type.
// That is, Meta_Reference pointer can be cast to a Meta_Feature pointer.
struct Meta_Reference
{
    // Meta_Feature fields
    Atomic refs;
    uint32 flags;
    const char* name;
    const Meta_Qualifier* const* meta_qualifiers;
    size_t num_meta_qualifiers;

    // Local fields
    sint16 subscript;
    const Meta_Class* meta_class;
    uint32 offset;
};

CIMPLE_CIMPLE_LINKAGE
Meta_Reference* clone(const Meta_Reference* mr);

CIMPLE_CIMPLE_LINKAGE
void destroy(Meta_Reference* mr);

CIMPLE_CIMPLE_LINKAGE
void print(const Meta_Reference* mr);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Reference_h */
