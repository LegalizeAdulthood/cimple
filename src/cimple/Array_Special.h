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

template <> 
class Array<CIMPLE_T> : public Array_Base
{
public:

    Array() : Array_Base(sizeof(CIMPLE_T)) 
    { 
    }

    Array(const CIMPLE_T* data, size_t size) : 
	Array_Base(sizeof(CIMPLE_T), data, size) 
    {
    }

    Array(const Array<CIMPLE_T>& x) : Array_Base(x) 
    { 
    }

    Array<CIMPLE_T>& operator=(const Array<CIMPLE_T>& x)
    {
	_assign(x);
	return *this;
    }

    void clear()
    {
	remove(0, _rep->size);
    }

    size_t size() const 
    { 
	return _rep->size; 
    }

    size_t capacity() const 
    { 
	return _rep->cap; 
    }

    const CIMPLE_T* data() const 
    { 
	return (CIMPLE_T*)_rep->data; 
    }

    CIMPLE_T* data() 
    { 
	return (CIMPLE_T*)_rep->data; 
    }

    CIMPLE_T& operator[](size_t pos) 
    { 
	return ((CIMPLE_T*)_rep->data)[pos]; 
    }

    const CIMPLE_T& operator[](size_t pos) const 
    { 
	return ((CIMPLE_T*)_rep->data)[pos]; 
    }

    void resize(size_t size) 
    {
	static CIMPLE_T x;
	_resize(size, &x); 
    }

    void assign(const Array<CIMPLE_T>& x) 
    { 
	_assign(x); 
    }

    void assign(const CIMPLE_T* data, size_t size) 
    { 
	_assign(data, size); 
    }

    void swap(Array<CIMPLE_T>& x) 
    { 
	_swap(x); 
    }

    void insert(size_t pos, const CIMPLE_T* data, size_t size)
    {
	_insert(pos, data, size);
    }

    void insert(size_t pos, const CIMPLE_T& elem)
    {
	_insert(pos, &elem, 1);
    }

    void append(const CIMPLE_T* data, size_t size)
    {
	_append(data, size);
    }

    void append(const CIMPLE_T& elem)
    {
	_append(&elem, 1);
    }

    void prepend(const CIMPLE_T* data, size_t size)
    {
	_prepend(data, size);
    }

    void prepend(const CIMPLE_T& elem)
    {
	_prepend(&elem, 1);
    }

    void remove(size_t pos, size_t size)
    {
	_remove(pos, size);
    }

    void remove(size_t pos)
    {
	_remove(pos, 1);
    }
};
