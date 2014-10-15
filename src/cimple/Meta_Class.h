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
};

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Feature* find_feature(
    const Meta_Class* mc, const char* name, uint32 type = 0xFFFFFFFF);

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Property* find_property(const Meta_Class* mc, const char* name);

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Reference* find_reference(const Meta_Class* mc, const char* name);

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Method* find_method(const Meta_Class* mc, const char* name);

CIMPLE_LIBCIMPLE_LINKAGE
bool has_methods(const Meta_Class* mc);

CIMPLE_LIBCIMPLE_LINKAGE
bool has_references(const Meta_Class* mc);

CIMPLE_LIBCIMPLE_LINKAGE
size_t count_keys(const Meta_Class* mc);

CIMPLE_LIBCIMPLE_LINKAGE
extern Meta_Class Instance_meta_class;

typedef void (*Repository_Proc)(const Meta_Class* const*&, size_t&);

CIMPLE_LIBCIMPLE_LINKAGE
const Meta_Class* find_meta_class(
    const Meta_Class* const*meta_classes, 
    size_t num_meta_classes,
    const char* class_name);

CIMPLE_LIBCIMPLE_LINKAGE
bool is_local_feature(const Meta_Class* mc, const Meta_Feature* mf);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Class_h */
