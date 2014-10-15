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

#ifndef _cimple_Meta_Feature_h
#define _cimple_Meta_Feature_h

#include "config.h"
#include "Atomic.h"
#include "Meta_Qualifier.h"

CIMPLE_NAMESPACE_BEGIN

// This structure defines meta-data for a CIM class feature. It is a 
// pseudo-base type of Meta_Property, Meta_Reference, and Meta_Method. 
// These structures share the same two fields with this structure.
struct Meta_Feature
{
    Atomic refs;
    uint32 flags;
    const char* name;
    const Meta_Qualifier* const* meta_qualifiers;
    size_t num_meta_qualifiers;
};

// This structure defines feature-related attributes that are specific to
// one class. This is necessary since Meta_Features may be shared by two or 
// more classes in the class hierarchy.
struct Meta_Feature_Local
{
    // Whether feature is local to this class (if not, it was propagated from
    // another class).
    uint8 local;
};

CIMPLE_CIMPLE_LINKAGE
void destroy(Meta_Feature* mf);

CIMPLE_CIMPLE_LINKAGE
void print(const Meta_Feature* mf, bool print_qualifiers, size_t level);

CIMPLE_CIMPLE_LINKAGE
Meta_Feature* clone(const Meta_Feature* x);

CIMPLE_CIMPLE_LINKAGE
void append(
    const Meta_Feature* const*& meta_features,
    size_t& num_meta_features,
    const Meta_Feature* meta_feature);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Feature_h */
