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

#include <cstdarg>
#include "Meta_Class.h"
#include "Meta_Property.h"
#include "Meta_Repository.h"
#include "Meta_Qualifier.h"
#include "Instance.h"
#include "flags.h"
#include "Strings.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// ref()
//
//==============================================================================

void ref(const Meta_Class* mc)
{

    // Never increment refs in static instances (where refs == 0).
    if (mc && Atomic_get(&mc->refs))
        Atomic_inc(&((Meta_Class*)mc)->refs);
}

//==============================================================================
//
// unref()
//
//==============================================================================

void unref(const Meta_Class* mc)
{
    // Never destroy static instances (where refs == 0).
    if (mc && 
        Atomic_get(&mc->refs) && 
        Atomic_dec_and_test(&((Meta_Class*)mc)->refs))
    {
        destroy((Meta_Class*)mc);
    }
}

//==============================================================================
//
// __has_feature()
//
//==============================================================================

bool __has_feature(const Meta_Class* mc, uint32 type)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        if (mc->meta_features[i]->flags & type)
            return true;
    }

    return false;
}

//==============================================================================
//
// find_feature()
//
//==============================================================================

const Meta_Feature* find_feature(
    const Meta_Class* mc, const char* name, uint32 type)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        const Meta_Feature* mf = mc->meta_features[i];

        if (eqi(mf->name, name) && (mf->flags & type))
            return mf;
    }

    return 0;
}

//==============================================================================
//
// is_subclass()
//
//==============================================================================

bool is_subclass(const Meta_Class* ancestor, const Meta_Class* descendant)
{
    if (ancestor == &Instance::static_meta_class)
        return true;

    if (eqi(ancestor->name, "Instance"))
        return true;

    for (const Meta_Class* p = descendant; p; p = p->super_meta_class)
    {
        if (p == ancestor || eqi(p->name, ancestor->name))
            return true;
    }

    return false;
}

//==============================================================================
//
// find_meta_class()
//
//==============================================================================

const Meta_Class* find_meta_class(
    const Meta_Class* source_meta_class,
    const char* class_name)
{
    // Check this class.

    if (eqi(source_meta_class->name, class_name))
        return source_meta_class;

    // Check superclass chain.

    for (const Meta_Class* p = source_meta_class; 
        p; 
        p = p->super_meta_class)
    {
        if (eqi(p->name, class_name))
            return p;
    }

    // Check meta-repository.

    if (source_meta_class->meta_repository)
        return find_meta_class(source_meta_class->meta_repository, class_name);

    // Not found!
    return 0;
}

//==============================================================================
//
// print()
//
//==============================================================================

void print(const Meta_Class* mc, bool print_qualifiers, bool local_only)
{
    // Qualifiers:

    if (print_qualifiers)
    {
        print(mc->meta_qualifiers,
            mc->num_meta_qualifiers, mc->flags, false, 0);
    }

    // Class header:

    if (mc->super_meta_class)
        printf("class %s : %s\n", mc->name, mc->super_meta_class->name);
    else
        printf("class %s\n", mc->name);

    iprintf(0, "{\n");

    // Print features:

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        if (local_only && !mc->locals[i].local)
            continue;

        print(mc->meta_features[i], print_qualifiers, 1);
        printf(";\n");
    }

    // Class trailer:

    iprintf(0, "};\n");
}

//==============================================================================
//
// _identical_base()
//
//==============================================================================

static bool _identical_base(const Meta_Class* mc1, const Meta_Class* mc2)
{
    if (!mc1 != !mc2)
        return false;

    if (!mc1)
        return true;

    if (mc1->flags != mc2->flags)
        return false;

    if (!eqi(mc1->name, mc2->name))
        return false;

    if (mc1->num_meta_features != mc2->num_meta_features)
        return false;

    for (size_t i = 0; i < mc1->num_meta_features; i++)
    {
        const Meta_Feature* mf1 = mc1->meta_features[i];
        const Meta_Feature* mf2 = mc2->meta_features[i];

        if (mf1->flags != mf2->flags)
            return false;

        if (!eqi(mf1->name, mf2->name))
            return false;

        if (mf1->flags & CIMPLE_FLAG_PROPERTY)
        {
            const Meta_Property* mp1 = (const Meta_Property*)mf1;
            const Meta_Property* mp2 = (const Meta_Property*)mf2;

            if (mp1->type != mp2->type)
                return false;

            if (mp1->subscript != mp2->subscript)
                return false;

            if (mp1->offset != mp2->offset)
                return false;
        }

        if (mf1->flags & CIMPLE_FLAG_REFERENCE)
        {
            const Meta_Reference* mr1 = (const Meta_Reference*)mf1;
            const Meta_Reference* mr2 = (const Meta_Reference*)mf2;

            if (!identical(mr1->meta_class, mr2->meta_class))
                return false;

            if (mr1->offset != mr2->offset)
                return false;
        }

        if (mf1->flags & CIMPLE_FLAG_METHOD)
        {
            const Meta_Method* mm1 = (const Meta_Method*)mf1;
            const Meta_Method* mm2 = (const Meta_Method*)mf2;

            if (!_identical_base((Meta_Class*)mm1, (Meta_Class*)mm2))
                return false;

            if (mm1->return_type != mm2->return_type)
                return false;
        }
    }

    if (mc1->size != mc2->size)
        return false;

    // Identical:
    return true;
}

//==============================================================================
//
// identical()
//
//==============================================================================

bool identical(const Meta_Class* mc1, const Meta_Class* mc2)
{
    if (!_identical_base(mc1, mc2))
        return false;

    for (size_t i = 0; i < mc1->num_meta_features; i++)
        if (mc1->locals[i].local != mc2->locals[i].local)
            return false;

    if (!mc1)
        return true;

    if (mc1->super_meta_class && mc2->super_meta_class)
    {
        if (!identical(mc1->super_meta_class, mc2->super_meta_class))
            return false;
    }

    if (mc1->num_keys != mc2->num_keys)
        return false;

    // Identical:
    return true;
}

//==============================================================================
//
// destroy()
//
//==============================================================================

void destroy(Meta_Class* mc)
{
    if (!mc)
        return;

    // (Meta_Class|Meta_Method).name:

    free((char*)(mc->name));

    // (Meta_Class|Meta_Method).qualifiers:

    for (size_t i = 0; i < mc->num_meta_qualifiers; i++)
        destroy((Meta_Qualifier*)mc->meta_qualifiers[i]);

    free((Meta_Qualifier*)mc->meta_qualifiers);

    // (Meta_Class|Meta_Method).meta_features:

    for (size_t i = 0; i < mc->num_meta_features; i++)
        destroy((Meta_Feature*)mc->meta_features[i]);

    free((Meta_Feature**)mc->meta_features);

    // Meta_Class-only fields:

    if (!(mc->flags & CIMPLE_FLAG_METHOD))
    {
        // Meta_Class.locals:

        free((Meta_Feature_Local*)mc->locals);

        // Meta_Class.super_meta_class:

        unref(mc->super_meta_class);

        // Meta_Class.meta_repository (always null in dynamic Meta_Classes).

        // ATTN: remove:
        memset(mc, 0xDD, sizeof(Meta_Class));
    }
    else
    {
        // ATTN: remove:
        memset(mc, 0xDD, sizeof(Meta_Method));
    }

    Atomic_destroy(&mc->refs);

    free(mc);
}

//==============================================================================
//
// create_meta_class()
//
//==============================================================================

Meta_Class* create_meta_class(
    const char* name, 
    const Meta_Class* smc,
    uint32 flags)
{
    if (smc)
    {
        Meta_Class* mc = clone(smc);

        // Clear "Abstract" qualifier.
        {
            mc->flags &= ~CIMPLE_FLAG_ABSTRACT;
            const char* names[] = { "Abstract" };
            filter_qualifiers((Meta_Qualified_Object*)mc, names, 1);
        }

        // Meta_Class.name:

        free((char*)mc->name);
        *((char**)&mc->name) = strdup(name);

        // Meta_Class.locals:

        for (size_t i = 0; i < mc->num_meta_features; i++)
            ((Meta_Feature_Local*)mc->locals)[i].local = 0;

        // Meta_Class.super_meta_class:

        unref(mc->super_meta_class);
        ref(mc->super_meta_class = smc);

        return mc;
    }
    else
    {
        // Create Meta_Class:

        Meta_Class* mc = (Meta_Class*)calloc(1, sizeof(Meta_Class));
        Atomic_create(&mc->refs, 1);

        // Meta_Class.flags:

        mc->flags = flags;

        // Meta_Class.name:

        *((char**)&mc->name) = strdup(name);

        // Meta_Class.size:

        mc->size = sizeof(Instance);

        return mc;
    }
}

//==============================================================================
//
// clone()
//
//==============================================================================

Meta_Class* clone(const Meta_Class* x)
{
    // Create (Meta_Class|Meta_Method):

    size_t malloc_size;

    if (x->flags & CIMPLE_FLAG_METHOD)
        malloc_size = sizeof(Meta_Method);
    else
        malloc_size = sizeof(Meta_Class);

    Meta_Class* mc = (Meta_Class*)calloc(1, malloc_size);
    Atomic_create(&mc->refs, 1);

    // (Meta_Class|Meta_Method).flags:

    mc->flags = x->flags;

    // (Meta_Class|Meta_Method).name:

    *((char**)&mc->name) = strdup(x->name);

    // (Meta_Class|Meta_Method).meta_qualifiers:

    mc->meta_qualifiers = clone(x->meta_qualifiers, x->num_meta_qualifiers);
    mc->num_meta_qualifiers = x->num_meta_qualifiers;

    // (Meta_Class|Meta_Method).meta_features:

    if (x->num_meta_features)
    {
        Meta_Feature** meta_features = (Meta_Feature**)
            malloc(sizeof(Meta_Feature*) * x->num_meta_features);

        for (size_t i = 0; i < x->num_meta_features; i++)
            meta_features[i] = clone(x->meta_features[i]);

        mc->meta_features = meta_features;
        mc->num_meta_features = x->num_meta_features;
    }

    // (Meta_Class|Meta_Method).size:

    mc->size = x->size;

    // Meta_Class or Meta_Method?

    if (x->flags & CIMPLE_FLAG_METHOD)
    {
        // Method.return_type:
        ((Meta_Method*)mc)->return_type = ((Meta_Method*)x)->return_type;
    }
    else
    {
        // Meta_Method.locals:

        Meta_Feature_Local* locals = (Meta_Feature_Local*)malloc(
            sizeof(Meta_Feature_Local) * x->num_meta_features);

        memcpy(locals, x->locals,
            sizeof(Meta_Feature_Local) * x->num_meta_features);

        mc->locals = locals;

        // Meta_Class.super_meta_class:

        if (x->super_meta_class)
            ref(mc->super_meta_class = x->super_meta_class);

        // Meta_Class.num_keys:
        mc->num_keys = x->num_keys;

        // Meta_Class.meta_repository.
        mc->meta_repository = 0;
    }

    return mc;
}

// ATTN: finish
void dump(const Meta_Class* mc)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        if (mc->meta_features[i]->flags & CIMPLE_FLAG_PROPERTY)
        {
            Meta_Property* mp = (Meta_Property*)mc->meta_features[i];
            printf("[%s][%d]\n", mp->name, int(mp->offset));
        }
    }
}

void filter_qualifiers(
    Meta_Class* mc,
    const char* const* names,
    size_t num_names)
{
    // Filter class qualifiers:

    filter_qualifiers((Meta_Qualified_Object*)mc, names, num_names);

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
        Meta_Qualified_Object* mqo = 
            (Meta_Qualified_Object*)mc->meta_features[i];

        // Filter property, reference, and method qualifiers:

        if (mqo->flags & CIMPLE_FLAG_METHOD)
            filter_qualifiers((Meta_Class*)mqo, names, num_names);
        else
            filter_qualifiers(mqo, names, num_names);
    }
}

CIMPLE_NAMESPACE_END

