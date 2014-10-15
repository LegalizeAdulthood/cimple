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
#include <cassert>
#include <cstdlib>
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

void Array_Base::_destroy(char* data, size_t size)
{
    if (_dtor)
    {
	for (size_t i = 0; i < size; i++, data += _esize)
	    _dtor(data);
    }
}

void Array_Base::_copy(char* p, const char* q, size_t size)
{
    size_t nbytes = size * _esize;

    if (_ctor)
    {
	const char* end = p + nbytes;

	for (; p != end; p += _esize, q += _esize)
	    _ctor(p, q);
    }
    else
	memcpy(p, q, nbytes);
}

void Array_Base::_fill(char* p, size_t size, const void* elem)
{
    size_t nbytes = size * _esize;

    if (_ctor)
    {
	const char* end = p + nbytes;

	for (; p != end; p += _esize)
	    _ctor(p, elem);
    }
    else
	bzero(p, nbytes);
}

void Array_Base::_assign_no_release(const char* data, size_t size)
{
    _size = size;
    _cap = size;
    _data = 0;

    if (_size)
    {
	_data = (char*)malloc(_cap * _esize);
	_copy(_data, data, size);
	return;
    }
}

void Array_Base::_release()
{
    _destroy(_data, _size);
    free(_data);
}

void Array_Base::_construct(
    size_t esize, Ctor_Proc ctor, Dtor_Proc dtor, const void* data, size_t size)
{
    _esize = esize;
    _ctor = ctor;
    _dtor = dtor;
    _assign_no_release((char*)data, size);
}

Array_Base::Array_Base(size_t esize) : _esize(esize)
{
    bzero(this, sizeof(*this));
    _esize = esize;
}

Array_Base::Array_Base(size_t esize, Ctor_Proc ctor, Dtor_Proc dtor)
{
    bzero(this, sizeof(*this));
    _esize = esize;
    _ctor = ctor;
    _dtor = dtor;
}

Array_Base::Array_Base(const Array_Base& x)
{
    _construct(x._esize, x._ctor, x._dtor, x._data, x._size);
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
}

void Array_Base::reserve(size_t cap)
{
    if (cap > _cap)
    {
	const size_t GROWTH_FACTOR = 1;
	size_t r = GROWTH_FACTOR;

	while (r < cap)
	    r <<= 1;

	_cap = cap;
	_data = (char*)realloc(_data, _cap * _esize);
    }
}

void Array_Base::_resize(size_t size, const void* elem)
{
    ssize_t diff = size - _size;

    if (diff > 0)
    {
	reserve(size);
	_fill(_data + (_size * _esize), diff, elem);
    }
    else if (diff < 0)
	_destroy(_data + (size * _esize), -diff);

    _size = size;
}

void Array_Base::_assign(const Array_Base& x)
{
    _release();
    _assign_no_release(x._data, x._size);
}

void Array_Base::_assign(const void* data, size_t size)
{
    _release();
    _assign_no_release((char*)data, size);
}

void Array_Base::_swap(Array_Base& x)
{
    char* tdata = _data;
    size_t tsize = _size;
    size_t tcap = _cap;

    _data = x._data;
    _size = x._size;
    _cap = x._cap;

    x._data = tdata;
    x._size = tsize;
    x._cap = tcap;
}

void Array_Base::_insert(size_t pos, const void* data, size_t size)
{
    // assert(pos > _size);
    // assert(size != (size_t)-1);

    reserve(_size + size);
    char* ptr = (char*)(_data + pos * _esize);
    memmove(_data + (pos + size) * _esize, ptr, (_size - pos) * _esize);
    _copy(ptr, (char*)data, size);
    _size += size;
}

void Array_Base::_append(const void* data, size_t size)
{
    _insert(_size, data, size);
}

void Array_Base::_prepend(const void* data, size_t size)
{
    _insert(0, data, size);
}

void Array_Base::_remove(size_t pos, size_t size)
{
    // assert(pos + size <= _size);

    char* ptr = _data + pos * _esize;
    _destroy(ptr, size);
    memmove(ptr, 
	_data + (pos + size) * _esize, 
	(_size - (pos + size)) * _esize);
    _size -= size;
}

bool __equal(const Array_Base& x, const Array_Base& y)
{
    return x._size == y._size && 
	memcmp(x._data, y._data, x._size * x._esize) == 0;
}

bool __equal(const Array_Base& x, const Array_Base& y, Equal_Proc equal)
{
    if (x._size != y._size)
	return false;

    const char* p = x._data;
    const char* q = y._data;
    size_t esize = x._esize;

    for (size_t n = x._size; n--; p += esize, q += esize)
    {
	if (!equal(p, q))
	    return false;
    }

    return true;
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
