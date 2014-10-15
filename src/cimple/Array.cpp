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
#include <cassert>
#include <cstdlib>
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

void Array_Base::_destroy(char* data, size_t size)
{
    if (_rep->dtor)
    {
	for (size_t i = 0; i < size; i++, data += _rep->esize)
	    _rep->dtor(data);
    }
}

void Array_Base::_copy(char* p, const char* q, size_t size)
{
    size_t nbytes = size * _rep->esize;

    if (_rep->ctor)
    {
	const char* end = p + nbytes;

	for (; p != end; p += _rep->esize, q += _rep->esize)
	    _rep->ctor(p, q);
    }
    else
	memcpy(p, q, nbytes);
}

void Array_Base::_fill(char* p, size_t size, const void* elem)
{
    size_t nbytes = size * _rep->esize;

    if (_rep->ctor)
    {
	const char* end = p + nbytes;

	for (; p != end; p += _rep->esize)
	    _rep->ctor(p, elem);
    }
    else
	memset(p, 0, nbytes);
}

void Array_Base::_assign_no_release(const char* data, size_t size)
{
    _rep->size = size;
    _rep->cap = size;
    _rep->data = 0;

    if (_rep->size)
    {
	_rep->data = (char*)malloc(_rep->cap * _rep->esize);
	_copy(_rep->data, data, size);
	return;
    }
}

void Array_Base::_release()
{
    _destroy(_rep->data, _rep->size);
    free(_rep->data);
}

void Array_Base::_construct(
    size_t esize, Ctor_Proc ctor, Dtor_Proc dtor, const void* data, size_t size)
{
    _rep = new Array_Base_Rep;
    _rep->ctor = ctor;
    _rep->dtor = dtor;
    _rep->esize = esize;
    _assign_no_release((char*)data, size);
}

Array_Base::Array_Base(size_t esize)
{
    _rep = new Array_Base_Rep;
    memset(_rep, 0, sizeof(Array_Base_Rep));
    _rep->esize = esize;
}

Array_Base::Array_Base(size_t esize, Ctor_Proc ctor, Dtor_Proc dtor)
{
    _rep = new Array_Base_Rep;
    memset(_rep, 0, sizeof(Array_Base_Rep));
    _rep->esize = esize;
    _rep->ctor = ctor;
    _rep->dtor = dtor;
}

Array_Base::Array_Base(const Array_Base& x)
{
    _construct(
	x._rep->esize, x._rep->ctor, x._rep->dtor, x._rep->data, x._rep->size);
}

Array_Base::Array_Base(size_t esize, const void* data, size_t size)
{
    _construct(esize, 0, 0, data, size);
}

Array_Base::Array_Base(
    size_t esize, Ctor_Proc ctor, Dtor_Proc dtor, const void* data, size_t size)
{
    _construct(esize, ctor, dtor, data, size);
}

Array_Base::~Array_Base()
{
    _release();
    delete _rep;
}

void Array_Base::reserve(size_t cap)
{
    if (cap > _rep->cap)
    {
	const size_t GROWTH_FACTOR = 1;
	size_t r = GROWTH_FACTOR;

	while (r < cap)
	    r <<= 1;

	_rep->cap = cap;
	_rep->data = (char*)realloc(_rep->data, _rep->cap * _rep->esize);
    }
}

void Array_Base::_resize(size_t size, const void* elem)
{
    ssize_t diff = size - _rep->size;

    if (diff > 0)
    {
	reserve(size);
	_fill(_rep->data + (_rep->size * _rep->esize), diff, elem);
    }
    else if (diff < 0)
	_destroy(_rep->data + (size * _rep->esize), -diff);

    _rep->size = size;
}

void Array_Base::_assign(const Array_Base& x)
{
    _release();
    _assign_no_release(x._rep->data, x._rep->size);
}

void Array_Base::_assign(const void* data, size_t size)
{
    _release();
    _assign_no_release((char*)data, size);
}

void Array_Base::_swap(Array_Base& x)
{
    char* tdata = _rep->data;
    size_t tsize = _rep->size;
    size_t tcap = _rep->cap;

    _rep->data = x._rep->data;
    _rep->size = x._rep->size;
    _rep->cap = x._rep->cap;

    x._rep->data = tdata;
    x._rep->size = tsize;
    x._rep->cap = tcap;
}

void Array_Base::_insert(size_t pos, const void* data, size_t size)
{
    // assert(pos > _rep->size);
    // assert(size != (size_t)-1);

    reserve(_rep->size + size);
    char* ptr = (char*)(_rep->data + pos * _rep->esize);
    memmove(_rep->data + (pos + size) * _rep->esize, ptr, (_rep->size - pos) * _rep->esize);
    _copy(ptr, (char*)data, size);
    _rep->size += size;
}

void Array_Base::_append(const void* data, size_t size)
{
    _insert(_rep->size, data, size);
}

void Array_Base::_prepend(const void* data, size_t size)
{
    _insert(0, data, size);
}

void Array_Base::_remove(size_t pos, size_t size)
{
    // assert(pos + size <= _rep->size);

    char* ptr = _rep->data + pos * _rep->esize;
    _destroy(ptr, size);
    memmove(ptr, 
	_rep->data + (pos + size) * _rep->esize, 
	(_rep->size - (pos + size)) * _rep->esize);
    _rep->size -= size;
}

struct CIMPLE_HIDE Array_Friend
{
    static bool equal(const Array_Base& x, const Array_Base& y)
    {
	return x._rep->size == y._rep->size && memcmp(
	    x._rep->data, y._rep->data, x._rep->size * x._rep->esize) == 0;
    }

    static bool equal(
	const Array_Base& x, const Array_Base& y, Equal_Proc equal)
    {
	if (x._rep->size != y._rep->size)
	    return false;

	const char* p = x._rep->data;
	const char* q = y._rep->data;
	size_t esize = x._rep->esize;

	for (size_t n = x._rep->size; n--; p += esize, q += esize)
	{
	    if (!equal(p, q))
		return false;
	}

	return true;
    }
};

bool __equal(const Array_Base& x, const Array_Base& y)
{
    return Array_Friend::equal(x, y);
}

bool __equal(const Array_Base& x, const Array_Base& y, Equal_Proc equal)
{
    return Array_Friend::equal(x, y, equal);
}

bool Equal<String>::proc(const void* x, const void* y)
{
    return *((String*)x) == *((String*)y);
}

bool Equal<real32>::proc(const void* x, const void* y)
{
    return *((real32*)x) == *((real32*)y);
}

bool Equal<real64>::proc(const void* x, const void* y)
{
    return *((real64*)x) == *((real64*)y);
}

CIMPLE_NAMESPACE_END
