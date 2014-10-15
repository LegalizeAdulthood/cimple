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

#include <cstring>
#include <cstdarg>
#include "Instance.h"
#include "flags.h"
#include "Array.h"
#include "Property.h"
#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "Strings.h"

CIMPLE_NAMESPACE_BEGIN

void __construct(
    const Meta_Class* mc,
    Instance* inst)
{
    // Zero-fill the object (clearing the null).
    memset(inst, 0, mc->size);

    inst->meta_class = mc;
    inst->magic = CIMPLE_INSTANCE_MAGIC;

    // Initialize the reference count to one.

    Atomic_create(&inst->refs, 1);

    // The create() function has already zero-filled the object, which suffices
    // to initialize most properties. Others must be default constructed.
    // These include arrays and strings.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    void* prop = property_of(inst, mp);

	    if (mp->subscript)
	    {
		if (mp->type == STRING)
		    new (prop) Array_String();
		else
		    new (prop) Array_Base(type_size[mp->type]);
	    }
	    else
	    {
		if (mp->type == STRING)
		    new(prop) String();
	    }
	}
    }
}

Instance* create(const Meta_Class* mc)
{
    Instance* inst = (Instance*)operator new(mc->size);
    __construct(mc, inst);
    return inst;
}

Instance* create(const Meta_Method* meta_meth)
{
    return create((const Meta_Class*)meta_meth);
}

void __destruct(Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    // Release each Property:

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    void* field = property_of(inst, mp);

	    if (mp->subscript)
	    {
		((Array_Base*)field)->~Array_Base();
	    }
	    else
	    {
		if (mp->type == STRING)
		    ((String*)field)->~String();
	    }
	}
	else if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

	    Instance* instance = reference_of(inst, mr);

	    if (instance)
		destroy(instance);
	}
    }

    // Release the atomic reference count.

    Atomic_destroy(&inst->refs);
}

void destroy(Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    __destruct(inst);

#ifdef CIMPLE_DEBUG

    // Fill with bad characters to cause crash if used again.
    memset(inst, 0xDD, inst->meta_class->size);

#endif

    ::operator delete(inst);
}

bool identical(const Instance* i1, const Instance* i2)
{
    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i1->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i2->magic == CIMPLE_INSTANCE_MAGIC);

    // They must have the same meta class.

    if (i1->meta_class != i2->meta_class)
	return false;

    // Compare each feature.

    const Meta_Class* mc = i1->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];

	// Check that features are identical.

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = 
		(const Meta_Property*)mc->meta_features[i];

	    if (!property_eq((const Meta_Property*)mp, 
		property_of(i1, mp), property_of(i2, mp)))
		return false;
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = 
		(const Meta_Reference*)mc->meta_features[i];

	    const Instance* tmp1 = reference_of(i1, mr);
	    const Instance* tmp2 = reference_of(i2, mr);

	    if (tmp1 && tmp2 && !identical(tmp1, tmp2))
		return false;

	    if (tmp1 && !tmp2 || !tmp1 && tmp2)
		return false;
	}
    }

    // All features were identical.

    return true;
}

bool key_eq(const Instance* i1, const Instance* i2)
{
    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i1->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i2->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc1 = i1->meta_class;
    const Meta_Class* mc2 = i2->meta_class;

    // For each feature of i1.

    for (size_t i = 0; i < mc1->num_meta_features; i++)
    {
	const Meta_Feature* mf1 = mc1->meta_features[i];

	// Skip non-key features.

	if (!(mf1->flags & CIMPLE_FLAG_KEY))
	    continue;

	if (mf1->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp1 = (const Meta_Property*)mf1;
	    const Meta_Property* mp2 = find_property(mc2, mf1->name);

	    if (!mp2 || !(mp2->flags & CIMPLE_FLAG_KEY))
		return false;

	    if (mp1->type != mp2->type || mp1->subscript != mp2->subscript)
		return false;

	    if (!property_eq((const Meta_Property*)mp1, 
		property_of(i1, mp1), property_of(i2, mp2)))
		return false;
	}
	else if (mf1->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr2 = find_reference(mc2, mf1->name);
	    const Meta_Reference* mr1 = (const Meta_Reference*)mf1;

	    if (!mr2 || !(mr2->flags & CIMPLE_FLAG_KEY))
		return false;

	    if (!__is_a(mr1->meta_class, mr2->meta_class) &&
	        !__is_a(mr2->meta_class, mr1->meta_class))
	    {
		return false;
	    }

	    const Instance* ti1 = reference_of(i1, mr1);
	    const Instance* ti2 = reference_of(i2, mr2);

	    if (ti1 && ti2 && !key_eq(ti1, ti2))
		return false;

	    if (ti1 && !ti2 || !ti1 && ti2)
		return false;
	}
    }

    // All key properties were equal.
    return true;
}

// ATTN: fix copy to work between instances of different classes.
void __copy(Instance* i1, const Instance* i2, bool keys_only)
{
    // Check preconditions.

    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i1->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i2->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i1->meta_class == i2->meta_class);

    if (i1->meta_class != i2->meta_class)
	return;

    // Copy the properties.

    const Meta_Class* mc = i1->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (keys_only && !(flags & CIMPLE_FLAG_KEY))
	    continue;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    void* p1 = property_of(i1, mp);
	    const void* p2 = property_of(i2, mp);

	    null_of(mp, p1) = null_of(mp, p2);

	    if (mp->subscript)
		((Array_Base*)p1)->_assign(*((Array_Base*)p2));
	    else
	    {
		if (mp->type == STRING)
		    *((String*)p1) = *((String*)p2);
		else
		    memcpy(p1, p2, type_size[mp->type]);
	    }
	}
	else if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];
	    Instance*& r1 = reference_of(i1, mr);
	    const Instance* r2 = reference_of(i2, mr);

	    if (r1)
	    {
		destroy(r1);
		r1 = 0;
	    }

	    if (r2)
		r1 = clone(r2);
	}
    }
}

void copy(Instance* i1, const Instance* i2)
{
    __copy(i1, i2, false);
}

void copy_keys(Instance* i1, const Instance* i2)
{
    __copy(i1, i2, true);
}

void __uninitialized_copy(Instance* i1, const Instance* i2)
{
    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i2->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = i2->meta_class;

    // Initialize magic number.

    i1->magic = CIMPLE_INSTANCE_MAGIC;

    // Initialize meta class.

    i1->meta_class = mc;

    // Copy the raw objects using memcpy().

    memcpy(i1, i2, mc->size);

    // Copy objects requiring construction.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    void* p1 = property_of(i1, mp);
	    const void* p2 = property_of(i2, mp);

	    // Note: the null flags were copied above with memcpy().

	    if (mp->subscript)
		new(p1) Array_Base(*((Array_Base*)p2));
	    else
	    {
		if (mp->type == STRING)
		    new(p1) String(*((String*)p2));
	    }
	}
	else if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];
	    Instance*& r1 = reference_of(i1, mr);
	    const Instance*& r2 = reference_of(i2, mr);

	    if (r2)
		r1 = clone(r2);
	}
    }
}

Instance* clone(const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    Instance* new_inst = (Instance*)operator new(inst->meta_class->size);
    __uninitialized_copy(new_inst, inst);

    return new_inst;
}

Instance* key_clone(const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    Instance* new_inst = create(inst->meta_class);
    copy_keys(new_inst, inst);

    return new_inst;
}

void __set_null_flags(
    const Instance* inst, bool include_keys, bool include_non_keys, uint8 flag)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    uint8* prop = (uint8*)property_of(inst, mp);

	    if (flags & CIMPLE_FLAG_KEY)
	    {
		if (include_keys)
		    null_of(mp, prop) = flag;
	    }
	    else
	    {
		if (include_non_keys)
		    null_of(mp, prop) = flag;
	    }
	}
    }
}

ssize_t get_associators(
    const Instance* inst,
    const Instance* assoc_inst,
    const char* result_class,
    const char* role,
    const char* result_role,
    const Instance* associators[CIMPLE_MAX_REFERENCES_PER_CLASS])
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(assoc_inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(assoc_inst->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = assoc_inst->meta_class;

    size_t r = 0;

    bool found_inst = false;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];
	    const Instance* tmp = reference_of(assoc_inst, mr);

	    if (key_eq(inst, tmp))
	    {
		// Check role.

		if (role && *role != '\0')
		{
		    if (strcasecmp(mr->name, role) != 0)
			continue;
		}

		found_inst = true;
	    }
	    else
	    {
		// Check result class.

		if (result_class && *result_class != '\0')
		{
		    if (strcasecmp(tmp->meta_class->name, result_class) != 0)
			continue;
		}

		// Check result role.

		if (result_role && *result_role != '\0')
		{
		    if (strcasecmp(mr->name, result_role) != 0)
			continue;
		}

		associators[r++] = tmp;
	    }
	}
    }

    if (!found_inst)
	return -1;

    return r;
}

bool is_reference_of(
    const Instance* inst,
    const Instance* ref,
    const char* role)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(ref != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(ref->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ref->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];
	    const Instance* tmp = reference_of(ref, mr);

	    if (key_eq(inst, tmp))
	    {
		// Check role.

		if (role && *role != '\0')
		{
		    if (strcasecmp(mr->name, role) != 0)
			continue;
		}

		return true;
	    }
	}
    }

    return false;
}

bool __is_a(const Meta_Class* ancestor, const Meta_Class* descendant)
{
    while (descendant)
    {
	if ((void*)descendant == (void*)ancestor)
	    return true;

	descendant = descendant->super_meta_class;
    }

    return false;
}

bool is_descendent(const char* ancestor, const Meta_Class* descendant)
{
    while (descendant)
    {
	if ((void*)descendant == (void*)ancestor)
	    return true;

	descendant = descendant->super_meta_class;
    }

    return false;
}

#ifdef CIMPLE_NEED_RANDOM_INITIALIZE

////////////////////////////////////////////////////////////////////////////////
//
// Random initialialization of instances (should be moved out of core library).
//
////////////////////////////////////////////////////////////////////////////////

static void _random_value_initialize(Type type, void* p)
{
    switch (type)
    {
	case BOOLEAN:
	{
	    if ((rand() % 2) == 0)
		*((boolean*)p) = false;
	    else
		*((boolean*)p) = true;

	    break;
	}

	case UINT8:
	{
	    switch (rand() % 3)
	    {
		case 0: *((uint8*)p) = 99; break;
		case 1: *((uint8*)p) = CIMPLE_UINT8_MIN; break;
		case 2: *((uint8*)p) = CIMPLE_UINT8_MAX; break;
	    }
	    break;
	}

	case SINT8:
	{
	    switch (rand() % 3)
	    {
		case 0: *((sint8*)p) = 99; break;
		case 1: *((sint8*)p) = CIMPLE_SINT8_MIN; break;
		case 2: *((sint8*)p) = CIMPLE_SINT8_MAX; break;
	    }
	    break;
	}

	case UINT16:
	{
	    switch (rand() % 3)
	    {
		case 0: *((uint16*)p) = 99; break;
		case 1: *((uint16*)p) = CIMPLE_UINT16_MIN; break;
		case 2: *((uint16*)p) = CIMPLE_UINT16_MAX; break;
	    }
	    break;
	}

	case SINT16:
	{
	    switch (rand() % 3)
	    {
		case 0: *((sint16*)p) = 99; break;
		case 1: *((sint16*)p) = CIMPLE_SINT16_MIN; break;
		case 2: *((sint16*)p) = CIMPLE_SINT16_MAX; break;
	    }
	    break;
	}

	case UINT32:
	{
	    switch (rand() % 3)
	    {
		case 0: *((uint32*)p) = 1; break;
		case 1: *((uint32*)p) = 99999; break;
		case 2: *((uint32*)p) = CIMPLE_UINT32_MAX; break;
	    }
	    break;
	}

	case SINT32:
	{
	    switch (rand() % 3)
	    {
		case 0: *((sint32*)p) = 99; break;
		case 1: *((sint32*)p) = CIMPLE_SINT32_MIN; break;
		case 2: *((sint32*)p) = CIMPLE_SINT32_MAX; break;
	    }
	    break;
	}

	case UINT64:
	{
	    switch (rand() % 3)
	    {
		case 0: *((uint64*)p) = 99; break;
		case 1: *((uint64*)p) = CIMPLE_UINT64_MIN; break;
		case 2: *((uint64*)p) = CIMPLE_UINT64_MAX; break;
	    }
	    break;
	}

	case SINT64:
	{
	    switch (rand() % 3)
	    {
		case 0: *((sint64*)p) = 99; break;
		case 1: *((sint64*)p) = CIMPLE_SINT64_MIN; break;
		case 2: *((sint64*)p) = CIMPLE_SINT64_MAX; break;
	    }
	    break;
	}

	case REAL32:
	{
	    switch (rand() % 3)
	    {
		case 0: *((real32*)p) = 99.0; break;
		case 1: *((real32*)p) = -32.0; break;
		case 2: *((real32*)p) = +32.0; break;
	    }
	    break;
	}

	case REAL64:
	{
	    switch (rand() % 3)
	    {
		case 0: 
		    *((real64*)p) = 99.0; 
		    break;

		case 1: 
		    *((real64*)p) = -64.0; 
		    break;

		case 2: 
		    *((real64*)p) = 64.0; 
		    break;
	    }
	    break;
	}

	case CHAR16:
	{
	    switch (rand() % 6)
	    {
		case 0: *((char16*)p) = 1; break;
		case 1: *((char16*)p) = CIMPLE_UINT8_MIN; break;
		case 2: *((char16*)p) = CIMPLE_UINT8_MAX; break;
		case 3: *((char16*)p) = 'A'; break;
		case 4: *((char16*)p) = 'B'; break;
		case 5: *((char16*)p) = 'C'; break;
	    }
	    break;
	}

	case DATETIME:
	{
	    *((Datetime*)p) = Datetime::now();
	    break;
	}

	case STRING:
	{
	    switch (rand() % 3)
	    {
		case 0: *((String*)p) = String("empty"); break;
		case 1: *((String*)p) = String("Hello"); break;
		case 2: *((String*)p) = String("Goodbye"); break;
	    }
	    break;
	}
    }
}

void _random_property_initialize(
    const Meta_Property* mp, void* prop)
{
    Type type = Type(mp->type);

    if (mp->subscript == 0)
	_random_value_initialize(type, prop);
    else
    {
	char buf[16];
	String str;
	void* ptr;

	Array_Base* base = (Array_Base*)prop;
	base->_remove(0, base->_size);

	size_t size;

	if (mp->subscript == -1)
	    size = rand() % 4;
	else
	    size = mp->subscript;

	ptr = type == STRING ? (void*)&str : (void*)buf;

	for (size_t i = 0; i < size; i++)
	{
	    _random_value_initialize(type, ptr);
	    base->_append(ptr, 1);
	}
    }
}

void random_initialize(Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    _random_property_initialize(mp, property_of(inst, mp));
	}
	else if (flags & CIMPLE_FLAG_REFERENCE)
	{
#if 0
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];
	    Instance*& r = reference_of(inst, mr);

	    if (!r)
		r = create(mr->meta_class);

	    random_initialize(r);
#endif
	}
    }
}

#endif /* CIMPLE_NEED_RANDOM_INITIALIZE */

bool keys_non_null(const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	uint32 flags = mc->meta_features[i]->flags;

	// Skip non keys:

	if (!(flags & CIMPLE_FLAG_KEY))
	    continue;

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
	    const void* field = property_of(inst, mp);

	    if (null_of(mp, field))
		return false;
	}
	else if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];
	    const Instance* tmp = reference_of(inst, mr);

	    if (!tmp)
		return false;
	}
    }

    // If reached, all keys are defined.
    return true; 
}

int filter_properties(Instance* instance, const char* const* properties)
{
    CIMPLE_ASSERT(instance != 0);
    CIMPLE_ASSERT(instance->magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = instance->meta_class;

    // Handle case where properties null.

    if (!properties)
    {
	de_nullify_properties(instance);
	return 0;
    }

    // Handle case where properties is non-null.

    nullify_non_keys(instance);

    while (*properties)
    {
	// Find the property:

	const Meta_Feature* mf = find_feature(mc, *properties++);

	if (!mf)
	{
	    // No such property!
	    return -1;
	}

	// Skip keys:

	if (mf->flags & CIMPLE_FLAG_KEY)
	    continue;

	// Validate the property:

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (const Meta_Property*)mf;
	    null_of(mp, property_of(instance, mp)) = 0;
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (const Meta_Reference*)mf;
	    Instance*& ref = reference_of(instance, mr);

	    if (!ref)
		ref = create(mr->meta_class);
	}
	else
	{
	    // Must be a method!
	    return -1;
	}
    }

    return 0;
}

void destroyer(Instance* p)
{
    if (p) 
	destroy(p); 
}

const char* class_name(const Instance* instance)
{
    CIMPLE_ASSERT(instance != 0);
    CIMPLE_ASSERT(instance->magic == CIMPLE_INSTANCE_MAGIC);
    return instance->meta_class->name;
}

void ref(const Instance* instance)
{
    if (instance)
	Atomic_inc(&((Instance*)instance)->refs);
}

void unref(const Instance* instance)
{
    if (instance && Atomic_dec_and_test(&((Instance*)instance)->refs))
	destroy((Instance*)instance);
}

CIMPLE_NAMESPACE_END
