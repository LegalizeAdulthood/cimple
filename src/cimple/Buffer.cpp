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

#include "Buffer.h"
#include <cstdarg>

#define MIN_CAPACITY 4096

CIMPLE_NAMESPACE_BEGIN

static size_t _round_up_pow_2(size_t x)
{
    if (x < MIN_CAPACITY)
        return MIN_CAPACITY;

    x--;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
#if __WORDSIZE == 64
    x |= (x >> 32);
#endif
    x++;

    return x;
}

Buffer::Buffer() : _data(0), _size(0), _cap(0) 
{ 
}

Buffer::Buffer(const Buffer& x)
{
    _size = x._size;
    _cap = x._size;
    _data = (char*)malloc(_cap);
    memcpy(_data, x._data, _size);
}

Buffer::~Buffer() 
{ 
    free(_data); 
}

Buffer& Buffer::operator=(const Buffer& x)
{
    if (&x != this)
    {
	free(_data);
	_size = x._size;
	_cap = x._size;
	_data = (char*)malloc(_cap);
	memcpy(_data, x._data, _size);
    }

    return *this;
}

void Buffer::reserve(size_t capacity)
{
    if (capacity > _cap)
    {
	if (capacity < MIN_CAPACITY)
	    capacity = MIN_CAPACITY;

	_data = (char*)realloc(_data, capacity);
	_cap = capacity;
    }
}

void Buffer::remove(size_t i, size_t size)
{
    CIMPLE_ASSERT(i + size <= _size);

    size_t rem = _size - (i + size);

    if (rem)
	memmove(_data + i, _data + i + size, rem);

    _size -= size;
}

void Buffer::_append_aux()
{
    reserve(_cap ? _cap * 2 : MIN_CAPACITY);
}

void Buffer::insert(size_t i, const char* data, size_t size)
{
    CIMPLE_ASSERT(i <= _size);

    size_t new_size = _size + size;	
    size_t rem = _size - i;

    if (new_size > _cap)
    {
	size_t new_cap = _round_up_pow_2(new_size);
	char* new_data = (char*)malloc(new_cap);
	memcpy(new_data, _data, i);
	memcpy(new_data + i, data, size);
	memcpy(new_data + i + size, _data + i, rem);
	free(_data);
	_data = new_data;
	_size = new_size;
	_cap = new_cap;
    }
    else
    {
	if (rem)
	    memmove(_data + i + size, _data + i, rem);

	memcpy(_data + i, data, size);
	_size += size;
    }
}

size_t Buffer::appendf(const char* format, ...)
{
    size_t size = 128;
    va_list ap;

    for (;;)
    {
	reserve(_size + size);
	char* str = _data + _size;

	va_start(ap, format);
	int n = vsnprintf(str, size, format, ap);
	va_end(ap);

	if (n > -1 && n < int(size))
	{
	    _size += n;
	    return size_t(n);
	}

	if (n > -1)
	    size = n + 1;
	else
	    size *= 2;
    }

    // Unreachable:
    return 0;
}

void Buffer::append_uint16(uint16 x)
{
    char buffer[5];
    char* p = &buffer[5];

    do
    {
	*--p = '0' + (x % 10);
    }
    while ((x /= 10) != 0);

    append(p, &buffer[5] - p);
}

void Buffer::append_uint32(uint32 x)
{
    char buffer[10];
    char* p = &buffer[10];

    do
    {
	*--p = '0' + (x % 10);
    }
    while ((x /= 10) != 0);

    append(p, &buffer[10] - p);
}

void Buffer::append_uint64(uint64 x)
{
    char buffer[20];
    char* p = &buffer[20];

    do
    {
	*--p = '0' + (x % 10);
    }
    while ((x /= 10) != 0);

    append(p, &buffer[20] - p);
}

CIMPLE_NAMESPACE_END
