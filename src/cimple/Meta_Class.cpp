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
#include "Instance.h"
#include "flags.h"
#include "Strings.h"

#define BEGIN_TAG 0xBBBBBBBB
#define END_TAG 0xEEEEEEEE

CIMPLE_NAMESPACE_BEGIN

bool __has_feature(const Meta_Class* mc, uint32 type)
{
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	if (mc->meta_features[i]->flags & type)
	    return true;
    }

    return false;
}

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

const Meta_Class* find_meta_class(
    const Meta_Repository* mr,
    const char* class_name)
{
    for (size_t i = 0; i < mr->num_meta_classes; i++)
    {
	if (eqi(mr->meta_classes[i]->name, class_name))
	    return mr->meta_classes[i];
    }

    // Not found!
    return 0;
}

bool is_subclass(
    const Meta_Class* super_class, 
    const Meta_Class* sub_class)
{
    for (size_t i = 0; i < sub_class->num_super_classes; i++)
    {
	if (eqi(super_class->name, sub_class->super_classes[i]))
	    return true;
    }

    return false;
}

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

static void _check_flags(uint32 flags, const char* file, size_t line)
{
    uint32 mask = 
	CIMPLE_FLAG_PROPERTY|
	CIMPLE_FLAG_REFERENCE|
	CIMPLE_FLAG_METHOD|
	CIMPLE_FLAG_CLASS|
	CIMPLE_FLAG_ASSOCIATION|
	CIMPLE_FLAG_INDICATION|
	CIMPLE_FLAG_KEY|
	CIMPLE_FLAG_IN|
	CIMPLE_FLAG_OUT|
	CIMPLE_FLAG_LOCAL|
	CIMPLE_FLAG_EMBEDDED_OBJECT|
	CIMPLE_FLAG_STATIC;

    if ((flags & ~mask))
    {
	fprintf(stderr, "%s(%u): _check_flags() failed\n", file, uint32(line));
	abort();
    }
}

static int _iprintf(size_t level, const char* format, ...)
{
    printf("%*s", int(level * 4), "");

    va_list ap;
    va_start(ap, format);
    int r = vprintf(format, ap);
    va_end(ap);

    return r;
}

static void _dump_flags(uint32 flags, size_t level)
{
    _iprintf(level, "flags=");

    const char* strings[32];
    size_t n = 0;

    if (flags & CIMPLE_FLAG_PROPERTY)
	strings[n++] = "PROPERTY";

    if (flags & CIMPLE_FLAG_REFERENCE)
	strings[n++] = "REFERENCE";

    if (flags & CIMPLE_FLAG_METHOD)
	strings[n++] = "METHOD";

    if (flags & CIMPLE_FLAG_CLASS)
	strings[n++] = "CLASS";

    if (flags & CIMPLE_FLAG_ASSOCIATION)
	strings[n++] = "ASSOCIATION";

    if (flags & CIMPLE_FLAG_INDICATION)
	strings[n++] = "INDICATION";

    if (flags & CIMPLE_FLAG_KEY)
	strings[n++] = "KEY";

    if (flags & CIMPLE_FLAG_IN)
	strings[n++] = "IN";

    if (flags & CIMPLE_FLAG_OUT)
	strings[n++] = "OUT";

    if (flags & CIMPLE_FLAG_LOCAL)
	strings[n++] = "LOCAL";

    if (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
	strings[n++] = "EMBEDDED_OBJECT";

    if (flags & CIMPLE_FLAG_STATIC)
	strings[n++] = "STATIC";

    for (size_t i = 0; i < n; i++)
    {
	printf("%s", strings[i]);

	if (i + 1 != n)
	    putchar('|');
    }

    putchar('\n');
}

static void _dump_meta_property(const Meta_Property* mp, size_t level)
{
    _iprintf(level, "Meta_Property\n");
    _iprintf(level, "{\n");
    level++;

    // flags:
    _dump_flags(mp->flags, level);

    // name:
    _iprintf(level, "name=%s\n", mp->name);

    // type:
    _iprintf(level, "type=%s\n", type_name[mp->type]);

    // subscript:
    _iprintf(level, "subscript=%d\n", (sint32)mp->subscript);

    // offset:
    _iprintf(level, "offset=%ld\n", (unsigned long)(mp->offset));

    level--;
    _iprintf(level, "}\n");
}

static void _dump(const Meta_Class* mc, size_t level);

static void _dump_meta_reference(const Meta_Reference* mr, size_t level)
{
    _iprintf(level, "Meta_Reference\n");
    _iprintf(level, "{\n");
    level++;

    // flags:
    _dump_flags(mr->flags, level);

    // name:
    _iprintf(level, "name=%s\n", mr->name);

    // meta_class:
    _dump(mr->meta_class, level);

    // offset:
    _iprintf(level, "offset=%ld\n", (unsigned long)(mr->offset));

    level--;
    _iprintf(level, "}\n");
}

static void _dump_meta_method(const Meta_Method* mm, size_t level)
{
    _dump((Meta_Class*)mm, level);
}

static void _dump(const Meta_Class* mc, size_t level)
{
    if (mc->flags & CIMPLE_FLAG_METHOD)
	_iprintf(level, "struct Meta_Method\n");
    else
	_iprintf(level, "struct Meta_Class\n");

    _iprintf(level, "{\n");
    level++;

    // flags:
    _dump_flags(mc->flags, level);

    // name:
    _iprintf(level, "name=%s\n", mc->name);

    // meta_features:
    
    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	    _dump_meta_property((Meta_Property*)mf, level);

	if (mf->flags & CIMPLE_FLAG_REFERENCE)
	    _dump_meta_reference((Meta_Reference*)mf, level);

	if (mf->flags & CIMPLE_FLAG_METHOD)
	    _dump((Meta_Class*)mf, level);
    }

    if (mc->flags & CIMPLE_FLAG_METHOD)
    {
	_iprintf(level, "return_type: %u\n", ((Meta_Method*)mc)->return_type);
    }
    else
    {
	// locals:

	_iprintf(level, "locals\n");
	_iprintf(level, "{\n");
	level++;

	for (size_t i = 0; i < mc->num_meta_features; i++)
	{
	    _iprintf(level, "Meta_Feature_Local\n");
	    _iprintf(level, "{\n");
	    level++;
	    _iprintf(level, "%u\n", mc->locals[i].local ? 1 : 0);
	    level--;
	    _iprintf(level, "}\n");
	}

	level--;
	_iprintf(level, "}\n");

	// super_classes:
	_iprintf(level, "super_classes\n");
	_iprintf(level, "{\n");
	level++;

	for (size_t i = 0; i < mc->num_super_classes; i++)
	{
	    _iprintf(level, "\"%s,\"\n", mc->super_classes[i]);
	}

	level--;
	_iprintf(level, "}\n");

	// num_keys:
	_iprintf(level, "num_keys: %u\n", uint32(mc->num_keys));

	// crc:
	_iprintf(level, "crc: %09X\n", (uint32)mc->crc);
    }

    level--;
    _iprintf(level, "}\n");
}

void dump(const Meta_Class* mc)
{
    _dump(mc, 0);
}

//==============================================================================
//
// print()
//
//==============================================================================

static void _print_qualifiers(uint32 flags, size_t level)
{
    if ((CIMPLE_FLAG_ANY_QUALIFIER & flags) == 0)
    {
	_iprintf(level, "");
	return;
    }

    _iprintf(level, "[");

    const char* strings[32];
    size_t n = 0;

    if (flags & CIMPLE_FLAG_ASSOCIATION)
	strings[n++] = "Association";

    if (flags & CIMPLE_FLAG_INDICATION)
	strings[n++] = "Indication";

    if (flags & CIMPLE_FLAG_KEY)
	strings[n++] = "Key";

    if (flags & CIMPLE_FLAG_IN)
	strings[n++] = "In";

    if (flags & CIMPLE_FLAG_OUT)
	strings[n++] = "Out";

    if (flags & CIMPLE_FLAG_EMBEDDED_OBJECT)
	strings[n++] = "EmbeddedObject";

    if (flags & CIMPLE_FLAG_STATIC)
	strings[n++] = "Static";

    for (size_t i = 0; i < n; i++)
    {
	printf("%s", strings[i]);

	if (i + 1 != n)
	    printf(", ");
    }

    printf("] ");
}

static void _print_meta_property(const Meta_Property* mp, size_t level)
{
    _print_qualifiers(mp->flags, level);
    printf("%s %s", type_name[mp->type], mp->name);

    if (mp->subscript == -1)
	printf("[]");
    else if (mp->subscript != 0)
	printf("[%d]", mp->subscript);
}

static inline void _print_meta_reference(const Meta_Reference* mr, size_t level)
{
    _print_qualifiers(mr->flags, level);
    printf("%s ref %s", mr->meta_class->name, mr->name);
}

static void _print_meta_method(const Meta_Method* mm, size_t level)
{
    _print_qualifiers(mm->flags, level);
    printf("%s %s(", type_name[mm->return_type], mm->name);

    assert(mm->num_meta_features > 0);

    size_t n = mm->num_meta_features;

    // Ignore final "return_value" parameter.
    
    if (mm->num_meta_features > 0)
	n--;

    for (size_t i = 0; i < n; i++)
    {
	putchar('\n');
	const Meta_Feature* mf = mm->meta_features[i];

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	    _print_meta_property((Meta_Property*)mf, level+1);

	if (mf->flags & CIMPLE_FLAG_REFERENCE)
	    _print_meta_reference((Meta_Reference*)mf, level+1);

	if (i + 1 != n)
	    printf(",");
    }

    printf(")");
}

void print(const Meta_Class* mc)
{
    // Qualifiers:
    _print_qualifiers(mc->flags, 0);

    // Class header:

    if (mc->num_super_classes)
	printf("class %s : %s\n", mc->name, mc->super_classes[0]);
    else
	printf("class %s\n", mc->name);

    _iprintf(0, "{\n");

    // Print features:

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	    _print_meta_property((Meta_Property*)mf, 1);

	if (mf->flags & CIMPLE_FLAG_REFERENCE)
	    _print_meta_reference((Meta_Reference*)mf, 1);

	if (mf->flags & CIMPLE_FLAG_METHOD)
	    _print_meta_method((Meta_Method*)mf, 1);

	printf(";\n");
    }

    // Class trailer:

    _iprintf(0, "};\n");
}

//==============================================================================
//
// identical()
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

bool identical(const Meta_Class* mc1, const Meta_Class* mc2)
{
    if (!_identical_base(mc1, mc2))
	return false;

    for (size_t i = 0; i < mc1->num_meta_features; i++)
	if (mc1->locals[i].local != mc2->locals[i].local)
	    return false;

    if (!mc1)
	return true;

    if (mc1->num_super_classes != mc2->num_super_classes )
	return false;

    for (size_t i = 0; i < mc1->num_super_classes; i++)
    {
	if (!eqi(mc1->super_classes[i], mc2->super_classes[i]))
	    return false;
    }

    if (mc1->num_keys != mc2->num_keys)
	return false;

    if (mc1->crc != mc2->crc)
	return false;

    // Ignore meta_repository!

    // Identical:
    return true;
}

//==============================================================================
//
// destroy()
//
//==============================================================================

static void _destroy(
    Meta_Class* mc, 
    Array<const Meta_Class*>& cache);

static void _destroy_base(
    Meta_Class* mc,
    Array<const Meta_Class*>& cache)
{
    if (!mc)
	return;

    delete [] (char*)(mc->name);

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	Meta_Feature* mf = mc->meta_features[i];


	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    Meta_Property* mp = (Meta_Property*)mf;
	    delete [] (char*)(mp->name);
	    delete mp;
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    Meta_Reference* mr = (Meta_Reference*)mf;
	    delete [] (char*)(mr->name);
	    _destroy((Meta_Class*)mr->meta_class, cache);
	    delete mr;
	}
	else if (mf->flags & CIMPLE_FLAG_METHOD)
	{
	    Meta_Method* mm = (Meta_Method*)mf;
	    _destroy_base((Meta_Class*)mm, cache);
	    delete mm;
	}
    }

    delete [] mc->meta_features;
}

static void _destroy(
    Meta_Class* mc, 
    Array<const Meta_Class*>& cache)
{
    // Don't destroy anything twice!

    if (cache.find((const Meta_Class*)mc) != (size_t)-1)
	return;

    if (!mc)
	return;

    _destroy_base(mc, cache);

    for (size_t i = 0; i < mc->num_super_classes; i++)
	delete [] (char*)(mc->super_classes[i]);

    delete [] (Meta_Feature_Local*)(mc->locals);
    delete [] (char**)mc->super_classes;

    cache.append(mc);
    delete mc;
}

void destroy(Meta_Class* mc)
{
    Array<const Meta_Class*> cache;
    _destroy(mc, cache);
}

CIMPLE_NAMESPACE_END
