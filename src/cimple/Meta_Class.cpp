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
#include "Enc.h"
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

static Meta_Class* _lookup(Array<const Meta_Class*>& cache, const char* name)
{
    for (size_t i = 0; i < cache.size(); i++)
    {
	if (eqi(cache[i]->name, name))
	    return (Meta_Class*)cache[i];
    }

    // Not found!
    return 0;
}

static void _pack_meta_class(
    Buffer& out, 
    const Meta_Class* mc,
    Array<const Meta_Class*>& cache);

static void _pack_meta_class_base(
    Buffer& out, 
    const Meta_Class* mc,
    Array<const Meta_Class*>& cache,
    bool& in_cache_out)
{
    in_cache_out = false;

    // If already in cache, just pack flags and name.

    if (!(mc->flags & CIMPLE_FLAG_METHOD) && _lookup(cache, mc->name))
    {
	pack_uint32(out, mc->flags | CIMPLE_FLAG_REDUNDANT);
	pack_c_str(out, mc->name);
	in_cache_out = true;
	return;
    }

    // flags:
    pack_uint32(out, mc->flags);

    // name:
    pack_c_str(out, mc->name);

    // meta_features:

    pack_size_t(out, mc->num_meta_features);

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = (Meta_Feature*)mc->meta_features[i];

	// Pack feature.

	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (Meta_Property*)mf;
	    pack_uint32(out, mp->flags);
	    pack_c_str(out, mp->name);
	    pack_uint16(out, mp->type);
	    pack_uint16(out, mp->subscript);
	    pack_uint32(out, mp->offset);
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (Meta_Reference*)mf;
	    pack_uint32(out, mr->flags);
	    pack_c_str(out, mr->name);
	    _pack_meta_class(out, mr->meta_class, cache);
	    pack_uint32(out, mr->offset);
	}
	else if (mf->flags & CIMPLE_FLAG_METHOD)
	{
	    const Meta_Method* mm = (Meta_Method*)mf;
	    bool flag;
	    _pack_meta_class_base(out, (const Meta_Class*)mm, cache, flag);
	    assert(flag == false);
	    pack_uint16(out, mm->return_type);
	}
	else 
	{
	    assert(0);
	}
    }

    // size:
    pack_uint32(out, mc->size);

    // Add to cache:

    if (!(mc->flags & CIMPLE_FLAG_METHOD))
	cache.append(mc);
}

static void _pack_meta_class(
    Buffer& out, 
    const Meta_Class* mc,
    Array<const Meta_Class*>& cache)
{
    // base:
    bool in_cache;
    _pack_meta_class_base(out, mc, cache, in_cache);

    if (in_cache)
	return;

    // locals:

    for (size_t i = 0; i < mc->num_meta_features; i++)
	pack_uint8(out, mc->locals[i].local);

    // super_classes:

    pack_size_t(out, mc->num_super_classes);

    for (size_t i = 0; i < mc->num_super_classes; i++)
	pack_c_str(out, mc->super_classes[i]);

    // Number of keys:
    pack_size_t(out, mc->num_keys);

    // CRC:
    pack_uint32(out, mc->crc);
}

void pack_meta_class(Buffer& out, const Meta_Class* mc)
{
    Array<const Meta_Class*> cache;
    return _pack_meta_class(out, mc, cache);
}

static void _dump_flags(uint32 flags, size_t level);

static inline char* _unpack_c_str(const Buffer& in, size_t& pos)
{
    const char* str;
    size_t size;
    unpack_c_str(in, pos, str, size);

    return (char*)memcpy(new char[size + 1], str, size + 1);
}

static Meta_Class* _unpack_meta_class(
    Buffer& in,
    size_t& pos,
    Array<const Meta_Class*>& cache);

Meta_Class* _unpack_meta_class_base(
    Buffer& in,
    size_t& pos,
    Array<const Meta_Class*>& cache,
    bool& in_cache_out)
{
    in_cache_out = false;

    // flags:

    uint32 flags;
    unpack_uint32(in, pos, flags);

    // name:

    char* name = _unpack_c_str(in, pos);

    // Is it already in cache!

    if (!(flags & CIMPLE_FLAG_METHOD) && (flags & CIMPLE_FLAG_REDUNDANT))
    {
	Meta_Class* mc = _lookup(cache, name);

	if (mc)
	{
	    delete [] name;
	    in_cache_out = true;
	    return mc;
	}

	// Should have been in cache!
	assert(0);
    }

    // Create object.

    Meta_Class* mc;

    if (flags & CIMPLE_FLAG_METHOD)
    {
	mc = (Meta_Class*)new Meta_Method;
	memset(mc, 0, sizeof(Meta_Method));
    }
    else
    {
	mc = new Meta_Class;
	memset(mc, 0, sizeof(Meta_Class));
    }

    mc->flags = flags;
    mc->name = name;

    // Meta-features:

    unpack_size_t(in, pos, mc->num_meta_features);

    if (mc->num_meta_features)
	mc->meta_features = new Meta_Feature*[mc->num_meta_features];

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	// Peek at the flags (do not advance position).
	uint32 flags;
	unpack_uint32(in, pos, flags);
	pos -= sizeof(uint32);

	// pos -= sizeof(uint64);

	// property:

	if (flags & CIMPLE_FLAG_PROPERTY)
	{
	    Meta_Property* mp = new Meta_Property;
	    unpack_uint32(in, pos, mp->flags);
	    mp->name = _unpack_c_str(in, pos);
	    unpack_uint16(in, pos, mp->type);
	    unpack_uint16(in, pos, *((uint16*)&mp->subscript));
	    unpack_uint32(in, pos, mp->offset);
	    mc->meta_features[i] = (Meta_Feature*)mp;
	}
	else if (flags & CIMPLE_FLAG_REFERENCE)
	{
	    Meta_Reference* mr = new Meta_Reference;
	    unpack_uint32(in, pos, mr->flags);
	    mr->name = _unpack_c_str(in, pos);
	    mr->meta_class = _unpack_meta_class(in, pos, cache);
	    unpack_uint32(in, pos, mr->offset);
	    mc->meta_features[i] = (Meta_Feature*)mr;
	}
	else if (flags & CIMPLE_FLAG_METHOD)
	{
	    bool flag;
	    Meta_Method* mm = 
		(Meta_Method*)_unpack_meta_class_base(in, pos, cache, flag);
	    assert(flag == false);
	    unpack_uint16(in, pos, mm->return_type);
	    mc->meta_features[i] = (Meta_Feature*)mm;
	}
	else
	{
	    assert(0);
	}
    }

    unpack_uint32(in, pos, mc->size);

    // Add to cache.

    if (!(mc->flags & CIMPLE_FLAG_METHOD))
	cache.append(mc);

    return mc;
}

static Meta_Class* _unpack_meta_class(
    Buffer& in,
    size_t& pos,
    Array<const Meta_Class*>& cache)
{
    // base:
    bool in_cache = false;
    Meta_Class* mc = _unpack_meta_class_base(in, pos, cache, in_cache);

    if (in_cache)
	return mc;

    // locals:

    if (mc->num_meta_features)
    {
	Meta_Feature_Local* locals =
	    new Meta_Feature_Local[mc->num_meta_features];

	memset(locals, 0, mc->num_meta_features * sizeof(Meta_Feature_Local));

	for (size_t i = 0; i < mc->num_meta_features; i++)
	    unpack_uint8(in, pos, locals[i].local);

	mc->locals = locals;
    }
    else
	mc->locals = 0;

    // super_classes:

    unpack_size_t(in, pos, mc->num_super_classes);

    if (mc->num_super_classes)
    {
	char** super_classes = new char*[mc->num_super_classes];

	for (size_t i = 0; i < mc->num_super_classes; i++)
	    super_classes[i] = _unpack_c_str(in, pos);

	mc->super_classes = super_classes;
    }
    else
	mc->super_classes = 0;

    unpack_size_t(in, pos, mc->num_keys);

    unpack_uint32(in, pos, mc->crc);

    return mc;
}

Meta_Class* unpack_meta_class(
    Buffer& in,
    size_t& pos)
{
    Array<const Meta_Class*> cache;
    return _unpack_meta_class(in, pos, cache);
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

    delete [] mc->name;

    for (size_t i = 0; i < mc->num_meta_features; i++)
    {
	const Meta_Feature* mf = mc->meta_features[i];


	if (mf->flags & CIMPLE_FLAG_PROPERTY)
	{
	    const Meta_Property* mp = (const Meta_Property*)mf;
	    delete [] mp->name;
	    delete mp;
	}
	else if (mf->flags & CIMPLE_FLAG_REFERENCE)
	{
	    const Meta_Reference* mr = (const Meta_Reference*)mf;
	    delete [] mr->name;
	    _destroy((Meta_Class*)mr->meta_class, cache);
	    delete mr;
	}
	else if (mf->flags & CIMPLE_FLAG_METHOD)
	{
	    const Meta_Method* mm = (const Meta_Method*)mf;
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

    if (find(cache, (const Meta_Class*)mc) != (size_t)-1)
	return;

    if (!mc)
	return;

    _destroy_base(mc, cache);

    for (size_t i = 0; i < mc->num_super_classes; i++)
	delete [] mc->super_classes[i];

    delete [] mc->locals;
    delete [] mc->super_classes;

    cache.append(mc);
    delete mc;
}

void destroy(Meta_Class* mc)
{
    Array<const Meta_Class*> cache;
    _destroy(mc, cache);
}

CIMPLE_NAMESPACE_END
