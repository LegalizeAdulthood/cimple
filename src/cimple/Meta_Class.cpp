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

#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Instance.h"
#include "flags.h"
#include "Enc.h"

CIMPLE_NAMESPACE_BEGIN

const Meta_Property* find_property(const Meta_Class* mc, const char* name)
{
    return (const Meta_Property*)find_feature(mc, name, CIMPLE_FLAG_PROPERTY);
}

const Meta_Reference* find_reference(const Meta_Class* mc, const char* name)
{
    return (const Meta_Reference*)find_feature(mc, name, CIMPLE_FLAG_REFERENCE);
}

const Meta_Method* find_method(const Meta_Class* mc, const char* name)
{
    return (const Meta_Method*)find_feature(mc, name, CIMPLE_FLAG_METHOD);
}

bool has_methods(const Meta_Class* mc)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	if (mc->meta_features[i]->flags & CIMPLE_FLAG_METHOD)
	    return true;
    }

    return false;
}

bool has_references(const Meta_Class* mc)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	if (mc->meta_features[i]->flags & CIMPLE_FLAG_REFERENCE)
	    return true;
    }

    return false;
}

size_t count_keys(const Meta_Class* mc)
{
    size_t n = 0;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* feature = mc->meta_features[i];

        if (feature->flags & CIMPLE_FLAG_KEY)
	    n++;
    }

    return n;
}

const Meta_Feature* find_feature(
    const Meta_Class* mc, const char* name, uint32 type)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];

	if (strcasecmp(mf->name, name) == 0 && mf->flags & type)
	    return mf;
    }

    return 0;
}

const Meta_Class* find_meta_class(
    const Meta_Repository* mr,
    const char* class_name)
{
    for (size_t i = 0; i < mr->num_meta_classes; i++)
    {
	if (strcasecmp(mr->meta_classes[i]->name, class_name) == 0)
	    return mr->meta_classes[i];
    }

    // Not found!
    return 0;
}

bool is_local_feature(const Meta_Class* mc, const Meta_Feature* mf)
{
    const Meta_Class* smc = mc->super_meta_class;

    // Must be local if there's no super class.

    if (!smc)
	return true;

    // Can't be local if the super class has it.

    for (size_t i = 0; i < smc->num_meta_features; i++)
    {
	if (mf == smc->meta_features[i])
	    return false;
    }

    // Must be local.

    return true;
}

// This is used for embedded objects.
Meta_Class Instance_meta_class =
{
    CIMPLE_FLAG_CLASS, /* flags */
    "Instance", /* name */
    0, /* meta_features */
    0, /* num_meta_features */
    sizeof(Instance), /* size */
    0, /* super_meta_class */
    0, /* num_keys */
    0x00000000, /* crc */
    0,
};

bool is_subclass(
    const Meta_Class* super_class, 
    const Meta_Class* sub_class)
{
    for (const Meta_Class* p = sub_class->super_meta_class; 
	p; 
	p = p->super_meta_class)
    {
	if (strcasecmp(p->name, super_class->name) == 0)
	    return true;
    }

    return false;
}

#if 0
void pack_meta_class(Buffer& out, const Meta_Class* mc)
{
    // Flags:

    pack_uint32(out, mc->flags);

    // Class name:

    pack_c_str(out, mc->name);

    // Number of meta-features:

    pack_uint32(out, mc->num_meta_features);

    // Size:

    pack_uint32(out, mc->size);

    // super class name:

    if (mc->super_meta_class)
	pack_c_str(out, mc->super_meta_class->name);
    else
	pack_uint32(out, 0);

    // Number of keys:

    pack_uint32(out, mc->num_keys);

    // CRC:

    pack_uint32(out, mc->crc);

    // Pack each feature.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = (Meta_Feature*)mc->meta_features[i];

	// Pack feature flags:

	pack_uint32(out, mf->flags);

	// Pack feature name:

	pack_c_str(out, mf->name);

	// Pack property.

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mf;
	    pack_uint16(out, mp->type);
	    pack_uint16(out, mp->subscript);
	    pack_uint32(out, mp->offset);
	}

	// Pack reference.

	if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mf;
	    pack_c_str(out, mr->meta_class->name);
	    pack_uint32(out, mr->offset);
	}
    }
}
#endif

const Meta_Class* find_meta_class(
    const Meta_Class* source_meta_class,
    const char* class_name)
{
    // Check this class.

    if (strcasecmp(source_meta_class->name, class_name) == 0)
	return source_meta_class;

    // Check superclass chain.

    for (const Meta_Class* p = source_meta_class; p; p = p->super_meta_class)
    {
	if (strcasecmp(p->name, class_name) == 0)
	    return p;
    }

    // Check meta-repository.

    if (source_meta_class->meta_repository)
	return find_meta_class(source_meta_class->meta_repository, class_name);

    // Not found!
    return 0;
}

CIMPLE_NAMESPACE_END
