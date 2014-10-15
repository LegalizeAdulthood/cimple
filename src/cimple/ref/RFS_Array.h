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

#ifndef _cimple_RFS_Array_h
#define _cimple_RFS_Array_h

#include <cstddef>
#include "config.h"

CIMPLE_NAMESPACE_BEGIN

/** This class implements a [R]aw [F]ixed-[S]ize array of N elements. The
    element type must be 'raw' (i.e., not requiring construction/destruction).
*/
template<class T, int N>
class RFS_Array
{
public:

    RFS_Array() : _size(0) { }

    size_t size() const { return _size; }

    T* data() { return _data; }

    const T* data() const { return _data; }

    T* end() { return _data + _size; }

    const T* end() const { return _data + _size; }

    void inc_size()
    {
	CIMPLE_ASSERT(_size < _N);
	_size++;
    }

    T& operator[](size_t i) 
    { 
	CIMPLE_ASSERT(i < _N);
	return _data[i]; 
    }

    const T& operator[](size_t i) const
    { 
	CIMPLE_ASSERT(i < _N);
	return _data[i]; 
    }

    void append(const T& x)
    {
	CIMPLE_ASSERT(_size < N);
	_data[_size++] = x;
    }

private:

    T _data[N];
    size_t _size;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Array_h */
