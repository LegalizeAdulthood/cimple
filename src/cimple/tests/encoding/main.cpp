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

#include <cassert>
#include <cctype>
#include <cimple/Enc.h>
#include "Everything.h"

using namespace cimple;

template<class T>
struct pack_array
{
    pack_array(Buffer& out, size_t n, const T& value)
    {
	Array<T> x;

	for (size_t i = 0; i < n; i++)
	    x.append(value);

	pack<T>(out, x);
    }
};

template<class T>
struct expect
{
    expect(const Buffer& in, size_t& pos, const T& value)
    {
	T x;
	unpack<T>(in, pos, x);
	assert(x == value);
    }
};

template<class T>
struct expect_array
{
    expect_array(const Buffer& in, size_t& pos, size_t n, const T& value)
    {
	Array<T> x;

	for (size_t i = 0; i < n; i++)
	    x.append(value);

	Array<T> y;
	unpack<T>(in, pos, y);
	assert(x == y);
    }
};

static const Meta_Class* _lookup(const char* class_name, void* client_data)
{
    if (strcasecmp(class_name, "Everything") == 0)
	return &Everything::static_meta_class;

    return 0;
}

template<class T>
struct make_array
{
    static Array<T> func(size_t size, const T& value)
    {
	Array<T> x;

	for (size_t i = 0; i < size; i++)
	    x.append(value);

	return x;
    }
};

int main(int argc, char** argv)
{
    {
	Buffer out;
	Datetime dt;

	pack<uint8>(out, 8);
	pack<boolean>(out, true);
	pack<uint8>(out, 8);
	pack<boolean>(out, false);
	pack<uint8>(out, 8);
	pack<uint8>(out, 8);
	pack<uint16>(out, 16);
	pack<uint8>(out, 8);
	pack<uint32>(out, 32);
	pack<uint8>(out, 8);
	pack<uint64>(out, 64);
	pack<uint8>(out, 8);
	pack<char16>(out, 'A');
	pack<uint8>(out, 8);
	pack<String>(out, "Hello");
	pack<uint8>(out, 8);
	pack<Datetime>(out, dt);
	pack<uint8>(out, 8);
	pack<real32>(out, 1.0);
	pack<uint8>(out, 8);
	pack<real64>(out, 1.0);

	Buffer in(out);
	size_t pos = 0;

	expect<uint8>(out, pos, 8);
	expect<boolean>(out, pos, true);
	expect<uint8>(out, pos, 8);
	expect<boolean>(out, pos, false);
	expect<uint8>(out, pos, 8);
	expect<uint16>(out, pos, 16);
	expect<uint8>(out, pos, 8);
	expect<uint32>(out, pos, 32);
	expect<uint8>(out, pos, 8);
	expect<uint64>(out, pos, 64);
	expect<uint8>(out, pos, 8);
	expect<char16>(out, pos, 'A');
	expect<uint8>(out, pos, 8);
	expect<String>(out, pos, "Hello");
	expect<uint8>(out, pos, 8);
	expect<Datetime>(out, pos, dt);
	expect<uint8>(out, pos, 8);
	expect<real32>(out, pos, 1.0);
	expect<uint8>(out, pos, 8);
	expect<real64>(out, pos, 1.0);

	assert(in.size() == pos);
    }

    // Test arrays.
    {
	Buffer out;
	Datetime dt;

	pack<uint8>(out, 8);
	pack_array<boolean>(out, 7, true);
	pack<uint8>(out, 8);
	pack_array<boolean>(out, 7, false);
	pack<uint8>(out, 8);
	pack_array<uint8>(out, 7, 8);
	pack<uint8>(out, 8);
	pack_array<uint16>(out, 3, 16);
	pack<uint8>(out, 8);
	pack_array<uint32>(out, 3, 32);
	pack<uint8>(out, 8);
	pack_array<uint64>(out, 3, 64);
	pack<uint8>(out, 8);
	pack_array<char16>(out, 3, 'A');
	pack<uint8>(out, 8);
	pack_array<String>(out, 3, "Hello");
	pack<uint8>(out, 8);
	pack_array<Datetime>(out, 3, dt);
	pack<uint8>(out, 8);
	pack_array<real32>(out, 3, 32.0);
	pack<uint8>(out, 8);
	pack_array<real64>(out, 3, 1.0);
	pack<uint8>(out, 8);

	Buffer in(out);
	size_t pos = 0;

	expect<uint8>(in, pos, 8);
	expect_array<boolean>(in, pos, 7, true);
	expect<uint8>(in, pos, 8);
	expect_array<boolean>(in, pos, 7, false);
	expect<uint8>(in, pos, 8);
	expect_array<uint8>(in, pos, 7, 8);
	expect<uint8>(in, pos, 8);
	expect_array<uint16>(in, pos, 3, 16);
	expect<uint8>(in, pos, 8);
	expect_array<uint32>(in, pos, 3, 32);
	expect<uint8>(in, pos, 8);
	expect_array<uint64>(in, pos, 3, 64);
	expect<uint8>(in, pos, 8);
	expect_array<char16>(in, pos, 3, 'A');
	expect<uint8>(in, pos, 8);
	expect_array<String>(in, pos, 3, "Hello");
	expect<uint8>(in, pos, 8);
	expect_array<Datetime>(in, pos, 3, dt);
	expect<uint8>(in, pos, 8);
	expect_array<real32>(in, pos, 3, 32.0);
	expect<uint8>(in, pos, 8);
	expect_array<real64>(in, pos, 3, 1.0);
	expect<uint8>(in, pos, 8);
    }

    // Instances:
    {
	Everything* inst1 = Everything::create();
	inst1->a.value = true;
	inst1->b.value = 8;
	inst1->c.value = 16;
	inst1->d.value = 32;
	inst1->e.value = 64;
	inst1->f.value = 32.0;
	inst1->g.value = 64.0;
	inst1->h.value = 'A';
	inst1->i.value = "Hello";
	inst1->j.value = Datetime::now();
	inst1->k.null = true;
	inst1->l.null = true;
	inst1->m.null = true;

	inst1->aa.value = make_array<boolean>::func(1, true);
	inst1->bb.value = make_array<uint8>::func(2, 8);
	inst1->cc.value = make_array<uint16>::func(3, 16);
	inst1->dd.value = make_array<uint32>::func(4, 32);
	inst1->ee.value = make_array<uint64>::func(1, 64);
	inst1->ff.value = make_array<real32>::func(2, 32.0);
	inst1->gg.value = make_array<real64>::func(3, 64.0);
	inst1->hh.value = make_array<char16>::func(4, 'A');
	inst1->ii.value = make_array<String>::func(3, "Hello");
	inst1->jj.value = make_array<Datetime>::func(2, Datetime::now());
	inst1->kk.null = true;
	inst1->ll.null = true;
	inst1->mm.null = true;

	// print(inst1);

	Buffer out;
	pack_instance(out, inst1);

	Buffer in(out);
	size_t pos = 0;

	Instance* inst2;

	if (unpack_instance(in, pos, _lookup, NULL, inst2) != 0)
	{
	    fprintf(stderr, "unpack_instance() failed\n");
	    exit(1);
	}

	// print(inst2);

	assert(identical(inst1, inst2));
    }

    printf("+++++ passed all tests (%s)\n", argv[0]);

    return 0;
}
