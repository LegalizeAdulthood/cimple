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

#include <cstring>
#include <cctype>
#include <cstdarg>
#include "Instance.h"
#include "flags.h"
#include "Array.h"
#include "Property.h"
#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "Strings.h"
#include "Ref.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

static void __default_construct(
    const Meta_Class* mc,
    Instance* inst,
    bool clear,
    bool defaults)
{
    // Grab meta-class:

    ref(mc);

    // Zero-fill the object (clearing the null).

    if (clear)
        memset(inst, 0, mc->size);

    inst->meta_class = mc;
    inst->__magic = CIMPLE_INSTANCE_MAGIC;

    // Initialize the reference count to one.

    Atomic_create(&inst->__refs, 1);

    // Initialize __name_space string.

    new(&inst->__name_space) String();

    // The create() function has already zero-filled the object, which suffices
    // to initialize most properties. Others must be default constructed.
    // These include arrays and strings.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
            void* prop = __property_of(inst, mp);

            if (mp->subscript)
            {
                // Default construct array:

                __Array_Base* base = (__Array_Base*)prop;
                __construct(base->rep, __cim_array_traits[mp->type]);

                // Assign array:

                if (defaults && mp->value)
                {
                    switch (mp->type)
                    {
                        case BOOLEAN:
                        case UINT8:
                        case SINT8:
                        case UINT16:
                        case SINT16:
                        case UINT32:
                        case SINT32:
                        case UINT64:
                        case SINT64:
                        case REAL32:
                        case REAL64:
                        case CHAR16:
                        {
                            __Array_Base* base = (__Array_Base*)prop;

                            Meta_Value_Array<void>* mv = 
                                (Meta_Value_Array<void>*)(mp->value);

                            __append(base->rep, mv->elements, mv->num_elements);
                            break;
                        }

                        case STRING:
                        {
                            Array<String>* base = (Array<String>*)prop;

                            Meta_Value_Array<char*>* mv = 
                                (Meta_Value_Array<char*>*)(mp->value);

                            for (size_t i = 0; i < mv->num_elements; i++)
                                base->append(String(mv->elements[i]));

                            break;
                        }

                        case DATETIME:
                        {
                            Array<Datetime>* base = (Array<Datetime>*)prop;

                            Meta_Value_Array<char*>* mv = 
                                (Meta_Value_Array<char*>*)(mp->value);

                            for (size_t i = 0; i < mv->num_elements; i++)
                            {
                                Datetime dt;
                                // ATTN: potential error ignored here!
                                dt.set(mv->elements[i]);
                                base->append(Datetime(dt));
                            }

                            break;
                        }
                    }
                }
                else
                {
                    if (defaults)
                        null_of(mp, prop) = 1;
                }
            }
            else
            {
                if (defaults && mp->value)
                {
                    switch (mp->type)
                    {
                        case BOOLEAN:
                        case UINT8:
                        case SINT8:
                        case UINT16:
                        case SINT16:
                        case UINT32:
                        case SINT32:
                        case UINT64:
                        case SINT64:
                        case REAL32:
                        case REAL64:
                        case CHAR16:
                            memcpy(prop, mp->value, type_size[mp->type]);
                            break;

                        case STRING:
                            new(prop) String(*((char**)mp->value));
                            break;

                        case DATETIME:
                            new(prop) Datetime();
                            // ATTN: potential error ignored here!
                            ((Datetime*)prop)->set(*((char**)mp->value));
                            break;
                    }
                }
                else
                {
                    if (mp->type == STRING)
                        new(prop) String();
                    else if (mp->type == DATETIME)
                        new(prop) Datetime();

                    if (defaults)
                        null_of(mp, prop) = 1;
                }
            }
        }
        else if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = 
                (const Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                Array_Ref& r = __array_ref_of(inst, mr);
                new(&r) Array_Ref;
            }
        }
    }
}

static void __uninitialized_copy(Instance* i1, const Instance* i2)
{
    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i2->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = i2->meta_class;

    // Copy the raw objects using memcpy().

    memcpy(i1, i2, mc->size);

    // Initialize reference count to 1.

    Atomic_create(&i1->__refs, 1);

    // Copy __name_space member.

    new(&i1->__name_space) String(i2->__name_space);

    // Copy features.

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
            void* p1 = __property_of(i1, mp);
            const void* p2 = __property_of(i2, mp);

            // Note: the null flags were copied above with memcpy().

            if (mp->subscript)
            {
                __construct(
                    ((__Array_Base*)p1)->rep,
                    ((const __Array_Base*)p2)->rep);
            }
            else
            {
                if (mp->type == STRING)
                    new(p1) String(*((String*)p2));
                else if (mp->type == DATETIME)
                    new(p1) Datetime(*((Datetime*)p2));
            }
        }
        else if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                Array_Ref& r1 = __array_ref_of(i1, mr);
                const Array_Ref& r2 = __array_ref_of(i2, mr);

                new(&r1) Array_Ref;

                for (size_t i = 0; i < r2.size(); i++)
                {
                    if (r2[i])
                        r1.append(clone(r2[i]));
                    else
                        r1.append(0);
                }
            }
            else
            {
                Instance*& r1 = __ref_of(i1, mr);
                const Instance*& r2 = __ref_of(i2, mr);

                if (r2)
                    r1 = clone(r2);
            }
        }
    }
}

static void __destruct(Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    // Release each Property:

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
            void* field = __property_of(inst, mp);

            if (mp->subscript)
                __destruct(((__Array_Base*)field)->rep);
            else
            {
                if (mp->type == STRING)
                    ((String*)field)->~String();
                else if (mp->type == DATETIME)
                    ((Datetime*)field)->~Datetime();
            }
        }
        else if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                Array_Ref& r = __array_ref_of(inst, mr);
                r.~Array_Ref();
            }
            else
            {
                Instance* instance = __ref_of(inst, mr);

                if (instance)
                    unref(instance);
            }
        }
    }

    // Release meta-class:

    unref(mc);

    // Release the atomic reference count.

    Atomic_destroy(&inst->__refs);

    // Destroy __name_space string.

    inst->__name_space.~String();
}

Instance* create(const Meta_Class* mc, bool defaults)
{
    Instance* inst = (Instance*)operator new(mc->size);
    __default_construct(mc, inst, true, defaults);
    return inst;
}

Instance* create(const Meta_Method* meta_meth)
{
    return create((const Meta_Class*)meta_meth);
}

void destroy(Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

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
    CIMPLE_ASSERT(i1->__magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i2->__magic == CIMPLE_INSTANCE_MAGIC);

    // They must have the same meta class.

    if (i1->meta_class != i2->meta_class)
        return false;

    // Check namespace field.

    if (i1->__name_space != i2->__name_space)
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
                __property_of(i1, mp), __property_of(i2, mp)))
                return false;
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = 
                (const Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                const Array_Ref& r1 = __array_ref_of(i1, mr);
                const Array_Ref& r2 = __array_ref_of(i2, mr);

                if (r1.size() != r2.size())
                    return false;

                for (size_t i = 0; i < r1.size(); i++)
                {
                    const Instance* tmp1 = r1[i];
                    const Instance* tmp2 = r2[i];

                    if (tmp1 && tmp2 && !identical(tmp1, tmp2))
                        return false;

                    if (tmp1 && !tmp2 || !tmp1 && tmp2)
                        return false;
                }
            }
            else
            {
                const Instance* tmp1 = __ref_of(i1, mr);
                const Instance* tmp2 = __ref_of(i2, mr);

                if (tmp1 && tmp2 && !identical(tmp1, tmp2))
                    return false;

                if (tmp1 && !tmp2 || !tmp1 && tmp2)
                    return false;
            }
        }
    }

    // All features were identical.

    return true;
}

bool key_eq(const Instance* i1, const Instance* i2)
{
    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i1->__magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i2->__magic == CIMPLE_INSTANCE_MAGIC);

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
                __property_of(i1, mp1), __property_of(i2, mp2)))
                return false;
        }
        else if (mf1->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr2 = find_reference(mc2, mf1->name);
            const Meta_Reference* mr1 = (const Meta_Reference*)mf1;

            if (mr1->subscript)
            {
                // Unreachable since reference arrays cannot be keys.
                continue;
            }

            if (!mr2 || !(mr2->flags & CIMPLE_FLAG_KEY))
                return false;

            if (!is_subclass(mr1->meta_class, mr2->meta_class) &&
                !is_subclass(mr2->meta_class, mr1->meta_class))
            {
                return false;
            }

            const Instance* ti1 = __ref_of(i1, mr1);
            const Instance* ti2 = __ref_of(i2, mr2);

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
static void __copy(Instance* i1, const Instance* i2, bool keys_only)
{
    // Check preconditions.

    CIMPLE_ASSERT(i1 != 0);
    CIMPLE_ASSERT(i2 != 0);
    CIMPLE_ASSERT(i1->__magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(i2->__magic == CIMPLE_INSTANCE_MAGIC);
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
            void* p1 = __property_of(i1, mp);
            const void* p2 = __property_of(i2, mp);

            null_of(mp, p1) = null_of(mp, p2);

            if (mp->subscript)
            {
                __assign(
                    ((__Array_Base*)p1)->rep,
                    (((const __Array_Base*)p2))->rep);
            }
            else
            {
                if (mp->type == STRING)
                    *((String*)p1) = *((String*)p2);
                else if (mp->type == DATETIME)
                    *((Datetime*)p1) = *((Datetime*)p2);
                else
                    memcpy(p1, p2, type_size[mp->type]);
            }
        }
        else if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                Array_Ref& r1 = __array_ref_of(i1, mr);
                const Array_Ref& r2 = __array_ref_of(i2, mr);

                r1.clear();

                for (size_t i = 0; i < r2.size(); i++)
                {
                    if (r2[i])
                        r1.append(clone(r2[i]));
                    else
                        r1.append(0);
                }
            }
            else
            {
                Instance*& r1 = __ref_of(i1, mr);
                const Instance* r2 = __ref_of(i2, mr);

                if (r1)
                {
                    unref(r1);
                    r1 = 0;
                }

                if (r2)
                    r1 = clone(r2);
            }
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

Instance* clone(const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    Instance* new_inst = (Instance*)operator new(inst->meta_class->size);
    __uninitialized_copy(new_inst, inst);

    return new_inst;
}

Instance* key_clone(const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    Instance* new_inst = create(inst->meta_class);
    copy_keys(new_inst, inst);

    return new_inst;
}

void __set_null_flags(
    const Instance* inst, bool include_keys, bool include_non_keys, uint8 flag)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
            uint8* prop = (uint8*)__property_of(inst, mp);

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
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(assoc_inst->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = assoc_inst->meta_class;
    bool found_inst = false;
    size_t r = 0;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                // Assocations may not contain arrays of references.
                continue;
            }

            const Instance* tmp = __ref_of(assoc_inst, mr);

            if (is_subclass(mr->meta_class, inst->meta_class) && 
                key_eq(inst, tmp))
            {
                // Check role.

                if (role && *role != '\0')
                {
                    if (!eqi(mr->name, role))
                        continue;
                }

                found_inst = true;
            }
            else
            {
                // Check result class.

                if (result_class && *result_class != '\0')
                {
                    bool found = false;

                    for (const Meta_Class* p = tmp->meta_class; 
                        p; 
                        p = p->super_meta_class)
                    {
                        if (eqi(result_class, p->name))
                        {
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                        continue;
                }

                // Check result role.

                if (result_role && *result_role != '\0')
                {
                    if (!eqi(mr->name, result_role))
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
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);
    CIMPLE_ASSERT(ref->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = ref->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                // Unreachable!
                continue;
            }

            const Instance* tmp = __ref_of(ref, mr);

            if (key_eq(inst, tmp))
            {
                // Check role.

                if (role && *role != '\0')
                {
                    if (!eqi(mr->name, role))
                        continue;
                }

                return true;
            }
        }
    }

    return false;
}

bool keys_non_null(const Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

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
            const void* field = __property_of(inst, mp);

            if (null_of(mp, field))
                return false;
        }
        else if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mc->meta_features[i];

            if (mr->subscript)
            {
                // Unreachable!
                continue;
            }

            const Instance* tmp = __ref_of(inst, mr);

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
    CIMPLE_ASSERT(instance->__magic == CIMPLE_INSTANCE_MAGIC);

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
            null_of(mp, __property_of(instance, mp)) = 0;
        }
        else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;

            if (mr->subscript)
            {
                // Unreachable!
                continue;
            }

            Instance*& ref = __ref_of(instance, mr);

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

void ref(const Instance* instance)
{
    if (instance)
        Atomic_inc(&((Instance*)instance)->__refs);
}

void unref(const Instance* instance)
{
    if (instance && Atomic_dec_and_test(&((Instance*)instance)->__refs))
        destroy((Instance*)instance);
}

//==============================================================================
//
// model_path_to_instance()
//
//==============================================================================

static bool _parse_identifier(const char*& p, String& ident)
{
    const char* start = p;

    if (!isalpha(*p) && *p != '_')
        return false;

    while (isalnum(*p) || *p == '_')
        p++;

    ident = String(start, p - start);
    return true;
}

static bool _parse_string_literal(const char*& p, String& lit)
{
    if (*p != '"')
        return false;

    p++;

    lit.clear();
    const char* start = p;

    while (*p && *p != '"')
    {
        if (*p == '\\')
        {
            p++;

            if ((*p != '\\') && (*p != '"'))
                return false;
        }

        lit.append(*p++);
    }

    return *p++ == '"';
}

static bool _str_to_sint64(const char*& str, sint64& x)
{
    // Try decimal.

    char* end;

#ifdef __USE_GNU

    x = strtoll(str, &end, 10);

#else

    // ATTN: hanlde overflow here!
    x = strtol(str, &end, 10);

#endif

    if (*end == '\0' || *end == ',')
    {
        str = end;
        return true;
    }

    // Try hexidecimal.

#if defined(__USE_GNU)

    x = strtoll(str, &end, 16);

#elif defined(CIMPLE_WINDOWS)

    // ATTN: hanlde overflow here!
    x = strtol(str, &end, 16);

#endif

    if (*end == '\0' || *end == ',')
    {
        str = end;
        return true;
    }

    // Failed.
    return false;
}

Instance* model_path_to_instance(
    const Meta_Class* source_meta_class, 
    const char* path)
{
    // ATTN: handle null values here!

    if (!source_meta_class)
        return 0;

    const char* p = path;

    // Get class name.

    String class_name;

    if (!_parse_identifier(p, class_name))
        return 0;

    // Lookup the class.

    const Meta_Class* mc = find_meta_class(
        source_meta_class, class_name.c_str());

    if (!mc)
        return 0;

    Ref<Instance> inst(create(mc));
    nullify_non_keys(inst.ptr());

    // Expect a '.' character.

    if (*p != '.')
        return 0;

    p++;

    // For each key=value pair.

    size_t num_keys_found = 0;

    while (*p)
    {
        // Get key name.

        String name;

        if (!_parse_identifier(p, name))
            return 0;

        // Find the feature.

        const Meta_Feature* mf = find_feature(mc, name.c_str());

        if (!mf || !(mf->flags & CIMPLE_FLAG_KEY))
            return 0;

        // Count the key.

        num_keys_found++;

        // Skip equal sign.

        if (*p++ != '=') 
            return 0;

        // Get value.

        if (mf->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (const Meta_Reference*)mf;

            if (mr->subscript)
            {
                // Unreachable!
                continue;
            }

            String value;

            if (!_parse_string_literal(p, value))
                return 0;

            Ref<Instance> tmp(model_path_to_instance(
                mr->meta_class, value.c_str()));

            if (!tmp)
                return 0;

            __ref_of(inst.ptr(), mr) = tmp.steal();
        }
        else if (mf->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (const Meta_Property*)mf;
            void* prop = __property_of(inst.ptr(), mp);

            switch (mp->type)
            {
                case BOOLEAN:
                {
                    const char* start = p;

                    while (*p && *p != ',')
                        p++;

                    size_t n = p - start;

                    if (n == 4 && strncasecmp(start, "true", 4) == 0)
                        *((boolean*)prop) = true;
                    else if (n == 5 && strncasecmp(start, "false", 5) == 0)
                        *((boolean*)prop) = false;
                    else
                        return 0;

                    break;
                }

                case UINT8:
                case SINT8:
                case UINT16:
                case SINT16:
                case UINT32:
                case SINT32:
                case UINT64:
                case SINT64:
                {
                    sint64 x;

                    if (!_str_to_sint64(p, x))
                        return 0;

                    switch (mp->type)
                    {
                        case UINT8:
                            *((uint8*)prop) = uint8(x);
                            break;

                        case SINT8:
                            *((sint8*)prop) = sint8(x);
                            break;

                        case UINT16:
                            *((uint16*)prop) = uint16(x);
                            break;

                        case SINT16:
                            *((sint16*)prop) = sint16(x);
                            break;

                        case UINT32:
                            *((uint32*)prop) = uint32(x);
                            break;

                        case SINT32:
                            *((sint32*)prop) = sint32(x);
                            break;

                        case UINT64:
                            *((uint64*)prop) = uint64(x);
                            break;

                        case SINT64:
                            *((sint64*)prop) = sint64(x);
                            break;

                        default:
                            ;
                    }

                    break;
                }

                case STRING:
                {
                    String value;

                    if (!_parse_string_literal(p, value))
                        return 0;

                    *((String*)prop) = value;
                    break;
                }

                default:
                    return 0;
            }
        }
        else
            return 0;

        // ATTN: double commas are ignored.

        if (*p == ',')
            p++;
    }

    if (num_keys_found != mc->num_keys)
        return 0;

    return inst.steal();
}

// This is used for embedded objects.
const Meta_Class Instance::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS, /* flags */
    "Instance", /* name */
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* meta_features */
    0, /* num_meta_features */
    sizeof(Instance), /* size */
    0, /* locals */
    0, /* super_meta_class */
    0, /* num_keys */
    0x00000000, /* crc */
    0, /* meta_repository */
};

//==============================================================================
//
// instance_to_model_path()
//
//==============================================================================

static int _append_key(const Meta_Property* mp, const void* prop, String& str)
{
    char buffer[64];

    switch (mp->type)
    {
        case BOOLEAN:
            sprintf(buffer, "%s", *((boolean*)prop) ? "true" : "false");
            break;

        case UINT8:
            sprintf(buffer, "%u", *((uint8*)prop));
            break;

        case SINT8:
            sprintf(buffer, "%d", *((sint8*)prop));
            break;

        case UINT16:
            sprintf(buffer, "%u", *((uint16*)prop));
            break;

        case SINT16:
            sprintf(buffer, "%d", *((sint16*)prop));
            break;

        case UINT32:
            sprintf(buffer, "%u", *((uint32*)prop));
            break;

        case SINT32:
            sprintf(buffer, "%d", *((sint32*)prop));
            break;

        case UINT64:
            sprintf(buffer, CIMPLE_LLU, *((uint64*)prop));
            break;

        case SINT64:
            sprintf(buffer, CIMPLE_LLD, *((sint64*)prop));
            break;

        case REAL32:
            sprintf(buffer, "%f", *((real32*)prop));
            break;

        case REAL64:
            sprintf(buffer, "%f", *((real64*)prop));
            break;

        case DATETIME:
            ((Datetime*)prop)->ascii(buffer);
            break;

        case CHAR16:
            // ATTN: handle escaping of characters here! UTF8
            sprintf(buffer, "'%c'", *((uint16*)prop));
            break;

        case STRING:
            // ATTN: handle escaping of characters here! UTF8
            str.append('"');
            str.append(*((String*)prop));
            str.append('"');
            return 0;
    }

    str.append(buffer);
    return 0;
}

static void _escape_quotes_and_append(String& out, const String& str)
{
    const char* p = str.c_str(); 
    
    while (*p)
    {
        char c = *p++;

        if (c == '"')
            out.append('\\');

        out.append(c);
    }
}

int instance_to_model_path(const Instance* inst, String& model_path)
{
    model_path.clear();

    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    // Reject instance without keys.

    if (mc->num_keys == 0)
        return -1;

    // Class name:

    model_path.append(mc->name);
    model_path.append('.');

    // Process keys:

    size_t num_keys_found = 0;
    
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;
        const Meta_Feature* mf = (Meta_Feature*)mc->meta_features[i];

        // Skip non-keys:

        if (!(flags & CIMPLE_FLAG_KEY))
            continue;

        // name:

        model_path.append(mf->name);
        model_path.append('=');

        // value:

        if (flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp = (Meta_Property*)mf;
            const void* prop = __property_of(inst, mp);

            // Arrays cannot be keys.

            if (mp->subscript)
                return -1;

            // ATTN: is this assumption correct?
            // Null-valued properties cannot be keys.

            if (null_of(mp, prop))
                return -1;

            _append_key(mp, prop, model_path);
        }
        if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = (Meta_Reference*)mf;

            if (mr->subscript)
            {
                // Unreachable!
                continue;
            }

            const Instance* tmp_instance = __ref_of(inst, mr);

            // ATTN: is this assumption correct?
            // A null reference cannot be a key.

            if (!tmp_instance)
                return -1;

            String tmp_model_path;

            if (instance_to_model_path(tmp_instance, tmp_model_path) != 0)
                return -1;

            model_path.append('"');
            _escape_quotes_and_append(model_path, tmp_model_path);
            model_path.append('"');
        }

        // Append comma:

        num_keys_found++;

        if (num_keys_found != mc->num_keys)
            model_path.append(',');
    }

    return 0;
}

namespace IO
{
    static void _print_scalar(uint32 type, const void* ptr)
    {
        switch (Type(type))
        {
            case BOOLEAN:
            {
                printf(*((boolean*)ptr) ?  "true" : "false");
                break;
            }

            case UINT8:
            {
                printf("%u", *((uint8*)ptr));
                break;
            }

            case SINT8:
            {
                printf("%d", *((sint8*)ptr));
                break;
            }

            case UINT16:
            {
                printf("%u", *((uint16*)ptr));
                break;
            }

            case SINT16:
            {
                printf("%d", *((sint16*)ptr));
                break;
            }

            case UINT32:
            {
                printf("%u", *((uint32*)ptr));
                break;
            }

            case SINT32:
            {
                printf("%d", *((sint32*)ptr));
                break;
            }

            case UINT64:
            {
                printf(CIMPLE_LLU, *((uint64*)ptr));
                break;
            }

            case SINT64:
            {
                printf(CIMPLE_LLD, *((sint64*)ptr));
                break;
            }

            case REAL32:
            {
                printf("%f", *((real32*)ptr));
                break;
            }

            case REAL64:
            {
                printf("%f", *((real64*)ptr));
                break;
            }

            case CHAR16:
            {
                uint16 c = *((uint16*)ptr);

                if (c >= ' ' && c <= '~')
                    printf("'%c'", c);
                else
                    printf("0x%04X", c);
                break;
            }

            case DATETIME:
            {
                char buffer[32];
                ((Datetime*)ptr)->ascii(buffer);
                printf("\"%s\"", buffer);
                break;
            }

            case STRING:
            {
                print_string(((String*)ptr)->c_str());
                break;
            }
        }
    }

    static void _print_array(uint32 type, const void* ptr, size_t depth)
    {
        printf("{ ");

        __Array_Base* base = (__Array_Base*)ptr;
        const char* data = base->rep->data;
        size_t size = base->rep->size;

        for (size_t i = 0; i < size; i++)
        {
            _print_scalar(type, data);

            if (i + 1 != size)
                putchar(',');

            putchar(' ');
            data += type_size[type];
        }

        printf("}");
    }

    static void _print_property(
        const Meta_Property* mp, const void* prop, size_t level)
    {
        iprintf(level, "%s %s", type_name[mp->type], mp->name);

        if (mp->subscript)
            printf("[]");

        printf(" = ");

        if (null_of(mp, prop))
            printf("NULL");
        else if (mp->subscript == 0)
            _print_scalar(mp->type, prop);
        else
            _print_array(mp->type, prop, 0);

        printf(";\n");
    }

    static void _print_aux(
        const Instance* inst, const char* name, size_t level, bool keys_only)
    {
        CIMPLE_ASSERT(inst != 0);
        CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

        const Meta_Class* mc = inst->meta_class;

        if (name)
            iprintf(level, "%s %s =\n", inst->meta_class->name, name);
        else
            iprintf(level, "%s\n", inst->meta_class->name);

        iprintf(level, "{\n");

        iprintf(level, 
            "    string __name_space = \"%s\";\n", inst->__name_space.c_str());

        for (size_t i = 0; i < mc->num_meta_features; i++)
        {
            uint32 flags = mc->meta_features[i]->flags;

            if (keys_only && !(flags & CIMPLE_FLAG_KEY))
                continue;

            // Skip non-keys if we are not at the top level.

            if (!(level == 0 || 
                (flags & CIMPLE_FLAG_KEY) || 
                (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)))
            {
                continue;
            }

            level++;

            if (flags & CIMPLE_FLAG_PROPERTY)
            {
                const Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
                const void* prop = __property_of(inst, mp);
                _print_property(mp, prop, level);
            }
            else if (flags & CIMPLE_FLAG_REFERENCE)
            {
                const Meta_Reference* mr = 
                    (Meta_Reference*)mc->meta_features[i];

                if (mr->subscript)
                {
                    const Array_Ref& r = __array_ref_of(inst, mr);

                    iprintf(level, "%s %s =\n", mr->meta_class->name, mr->name);
                    iprintf(level, "{\n");
                    level++;

                    for (size_t i = 0; i < r.size(); i++)
                    {
                        const Instance* tmp = r[i];

                        if (tmp)
                            _print_aux(tmp, 0, level, false);
                        else
                            iprintf(level, "NULL\n");
                    }

                    level--;
                    iprintf(level, "};\n");
                }
                else
                {
                    const Instance*& tmp = __ref_of(inst, mr);

                    if (tmp)
                        _print_aux(tmp, mr->name, level, keys_only);
                    else
                        iprintf(level, "%s %s = NULL;\n", 
                            mr->meta_class->name, mr->name);
                }
            }

            level--;
        }

        iprintf(level, "}\n");
    }
}

void print(const Instance* inst, bool keys_only)
{
    IO::_print_aux(inst, 0, 0, keys_only);
}

void __create_refs(Instance* inst)
{
    CIMPLE_ASSERT(inst != 0);
    CIMPLE_ASSERT(inst->__magic == CIMPLE_INSTANCE_MAGIC);

    const Meta_Class* mc = inst->meta_class;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        uint32 flags = mc->meta_features[i]->flags;

        if (flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr = 
                (const Meta_Reference*)mc->meta_features[i];

            if (mr->subscript == 0)
            {
                Instance*& r = __ref_of(inst, mr);

                if (r == 0)
                    r = create(mr->meta_class, true);
            }
        }
    }
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/Instance.cpp,v 1.119 2007/03/13 21:05:20 mbrasher-public Exp $");
