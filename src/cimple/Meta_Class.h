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

#ifndef _cimple_Meta_Class_h
#define _cimple_Meta_Class_h

#include "config.h"
#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "Meta_Method.h"

CIMPLE_NAMESPACE_BEGIN

struct Meta_Feature;

/** This structure defines meta-data for a particular CIM class.
*/
struct Meta_Class
{
    // Fields common with Meta_Method.
    uint32 flags;
    const char* name;
    Meta_Feature** meta_features; 
    size_t num_meta_features;
    uint32 size;

    // Local fields:
    const Meta_Class* super_meta_class;
    size_t num_keys;

    // 32-bit CRC over entire class:
    uint32 crc;

    // Backpointer to meta-repository (given any class, all other classes in
    // the same meta-repository can be obtained).
    const struct Meta_Repository* meta_repository;
};

struct Meta_Repository
{
    const Meta_Class* const* meta_classes;
    size_t num_meta_classes;
};

CIMPLE_LIBCIMPLE_LINKAGE
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

CIMPLE_LIBCIMPLE_LINKAGE
bool __has_feature(const Meta_Class* mc, uint32 type);

inline bool has_methods(const Meta_Class* mc)
{
    return __has_feature(mc, CIMPLE_FLAG_METHOD);
}

inline bool has_references(const Meta_Class* mc)
{
    return __has_feature(mc, CIMPLE_FLAG_REFERENCE);
}

CIMPLE_LIBCIMPLE_LINKAGE
bool is_local_feature(const Meta_Class* mc, const Meta_Feature* mf);

CIMPLE_LIBCIMPLE_LINKAGE
bool is_subclass(
    const Meta_Class* super_class, 
    const Meta_Class* sub_class);

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Class* find_meta_class(
    const Meta_Repository* meta_repository,
    const char* class_name);

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Class* find_meta_class(
    const Meta_Class* source_meta_class,
    const char* class_name);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Class_h */
