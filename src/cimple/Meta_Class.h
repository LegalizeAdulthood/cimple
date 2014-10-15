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
/*
    Structure and functions to define and access the meta data for CIM
    Classes. The user should never have to access this directly.  The
    genclass utility creates .h and .cpp files that use this structure
    and functions.
*/

#ifndef _cimple_Meta_Class_h
#define _cimple_Meta_Class_h

#include "config.h"
#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "Meta_Method.h"

CIMPLE_NAMESPACE_BEGIN

struct Meta_Feature;

// This structure defines meta-data for a particular CIM class.
struct Meta_Class
{
    // Fields common with Meta_Method.
    Atomic refs;
    uint32 flags;
    const char* name;
    const Meta_Qualifier* const* meta_qualifiers;
    size_t num_meta_qualifiers;
    const Meta_Feature* const* meta_features; 
    size_t num_meta_features;
    uint32 size;

    // Local fields:
    const Meta_Feature_Local* locals;
    const Meta_Class* super_meta_class;
    size_t num_keys;
    const struct Meta_Repository* meta_repository;
};

CIMPLE_CIMPLE_LINKAGE
void ref(const Meta_Class* mc);

CIMPLE_CIMPLE_LINKAGE
void unref(const Meta_Class* mc);

CIMPLE_CIMPLE_LINKAGE
const Meta_Feature* find_feature(
    const Meta_Class* mc, 
    const char* name, 
    uint32 type = CIMPLE_FLAG_ANY_FEATURE);

inline const Meta_Property* find_property(
    const Meta_Class* mc, 
    const char* name)
{
    return (const Meta_Property*)find_feature(mc, name, CIMPLE_FLAG_PROPERTY);
}

inline const Meta_Reference* find_reference(
    const Meta_Class* mc, 
    const char* name)
{
    return (const Meta_Reference*)find_feature(mc, name, CIMPLE_FLAG_REFERENCE);
}

inline const Meta_Method* find_method(
    const Meta_Class* mc, 
    const char* name)
{
    return (const Meta_Method*)find_feature(mc, name, CIMPLE_FLAG_METHOD);
}

CIMPLE_CIMPLE_LINKAGE
bool __has_feature(const Meta_Class* mc, uint32 type);

inline bool has_methods(const Meta_Class* mc)
{
    return __has_feature(mc, CIMPLE_FLAG_METHOD);
}

inline bool has_references(const Meta_Class* mc)
{
    return __has_feature(mc, CIMPLE_FLAG_REFERENCE);
}

CIMPLE_CIMPLE_LINKAGE
bool is_subclass(
    const Meta_Class* super_class, 
    const Meta_Class* sub_class);

CIMPLE_CIMPLE_LINKAGE
const Meta_Class* find_meta_class(
    const Meta_Class* source_meta_class,
    const char* class_name);

/** Creates a new meta class. Flags is ignored if super_meta_class is non-null.
    Else, flags must be one of the following:

        CIMPLE_FLAG_ASSOCIATION
        CIMPLE_FLAG_INDICATION
        CIMPLE_FLAG_CLASS
*/
CIMPLE_CIMPLE_LINKAGE
Meta_Class* create_meta_class(
    const char* name, 
    const Meta_Class* super_meta_class,
    uint32 flags);

CIMPLE_CIMPLE_LINKAGE
Meta_Class* clone(const Meta_Class* mc);

CIMPLE_CIMPLE_LINKAGE
void destroy(Meta_Class* mc);

CIMPLE_CIMPLE_LINKAGE
void print(const Meta_Class* mc, bool print_qualifiers, bool local_only = true);

CIMPLE_CIMPLE_LINKAGE
bool identical(const Meta_Class* mc1, const Meta_Class* mc2);

CIMPLE_CIMPLE_LINKAGE
void dump(const Meta_Class* mc);

CIMPLE_CIMPLE_LINKAGE
void filter_qualifiers(
    Meta_Class* mc,
    const char* const* names,
    size_t num_names);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Class_h */
