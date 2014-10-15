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

#ifndef _cimple_Meta_Method_h
#define _cimple_Meta_Method_h

#include "config.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "flags.h"

CIMPLE_NAMESPACE_BEGIN

// This structure defines meta-data for a CIM method. It shares initial
// fields with the Meta_Class structure.
struct Meta_Method
{
    // Fields common with Meta_Feature and Meta_Class.
    Atomic refs;
    uint32 flags;
    const char* name;
    const Meta_Qualifier* const* meta_qualifiers;
    size_t num_meta_qualifiers;

    // Fields common with Meta_Class only
    const Meta_Feature* const* meta_features;
    size_t num_meta_features;
    size_t size;

    // Local fields:
    uint16 return_type;
};

CIMPLE_CIMPLE_LINKAGE
const Meta_Feature* find_feature(
    const Meta_Method* mm, 
    const char* name, 
    uint32 type = CIMPLE_FLAG_ANY_FEATURE);

CIMPLE_CIMPLE_LINKAGE
const Meta_Property* find_parameter(const Meta_Method* mm, const char* name);

CIMPLE_CIMPLE_LINKAGE
const Meta_Reference* find_reference(const Meta_Method* mm, const char* name);

CIMPLE_CIMPLE_LINKAGE
void destroy(Meta_Method* mm);

CIMPLE_CIMPLE_LINKAGE
void print(const Meta_Method* mm, bool print_qualifiers, size_t level);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Method_h */
