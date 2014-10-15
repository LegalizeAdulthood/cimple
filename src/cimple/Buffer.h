/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006 Michael E. Brasher, K. Schopmeyer
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

#ifndef _cimple_Buffer_h
#define _cimple_Buffer_h

#include "config.h"
#include "linkage.h"
#include <cstdarg>

CIMPLE_NAMESPACE_BEGIN

//
// The Buffer class implements a simple array of raw types (types that do
// not require construction and deconstruction). It only implements the
// fundamentals: insertion of a single element at the rear and removal of
// a single element form the middle.
//
class CIMPLE_CIMPLE_LINKAGE Buffer
{
public:

    Buffer();

    Buffer(const Buffer& x);

    ~Buffer();

    Buffer& operator=(const Buffer& x);

    size_t size() const;

    size_t capacity() const;

    const char* data() const;

    char* data();

    const char* end() const;

    char* end();

    char operator[](size_t i) const;

    void set(size_t i, char x);

    void reserve(size_t capacity);

    void grow(size_t size);

    void resize(size_t size);

    void clear();

    void append(char x);

    void append(const char* data, size_t size);

    void remove(size_t i);

    void remove(size_t i, size_t size);

    void insert(size_t i, const char* data, size_t size);

    void appends(const char* str);

    CIMPLE_PRINTF_ATTR(2, 3)
    size_t format(const char* format, ...);

    size_t vformat(const char* format, va_list ap);

    void append_uint16(uint16 x);

    void append_uint32(uint32 x);

    void append_uint64(uint64 x);

private:

    void _append_aux();

    char* _data;
    size_t _size;
    size_t _cap;
};

inline size_t Buffer::size() const 
{ 
    return _size; 
}

inline size_t Buffer::capacity() const 
{ 
    return _cap; 
}

inline const char* Buffer::data() const 
{
    _data[_size] = '\0';
    return _data; 
}

inline char* Buffer::data() 
{
    _data[_size] = '\0';
    return _data; 
}

inline const char* Buffer::end() const 
{
    return _data + _size;
}

inline char* Buffer::end() 
{
    return _data + _size;
}

inline char Buffer::operator[](size_t i) const
{
    CIMPLE_ASSERT(i < _size);
    return _data[i]; 
}

inline void Buffer::set(size_t i, char x) 
{
    CIMPLE_ASSERT(i < _size);
    _data[i] = x; 
}

inline void Buffer::clear()
{
    _size = 0;
}

inline void Buffer::append(char x)
{
    if (_size == _cap)
        _append_aux();

    _data[_size++] = x;
}

inline void Buffer::append(const char* data, size_t size)
{
    if (_size + size > _cap)
        reserve(_size + size);

    memcpy(_data + _size, data, size);
    _size += size;
}

inline void Buffer::appends(const char* str)
{
    append(str, strlen(str));
}

inline void Buffer::remove(size_t i)
{
    remove(i, 1);
}

inline void Buffer::grow(size_t size)
{
    if (_size + size > _cap)
        reserve(_size + size);

    _size += size;
}

inline void Buffer::resize(size_t size)
{
    if (size > _cap)
        reserve(size);

    _size = size;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Buffer_h */
