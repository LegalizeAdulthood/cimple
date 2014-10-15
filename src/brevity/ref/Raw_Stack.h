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

#ifndef _cimple_Raw_Stack_h
#define _cimple_Raw_Stack_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

template<class T, size_t N>
class Raw_Stack
{
public:

    Raw_Stack();

    Raw_Stack(const Raw_Stack& x);

    ~Raw_Stack();

    Raw_Stack& operator=(const Raw_Stack& x);

    size_t size() const;

    size_t max_size() const { return N; }

    bool empty() const;

    void push(const T& x);

    void pop();

    const T& top() const;

    T& top();

private:
    T _rep[N];
    size_t _size;
};

template<class T, size_t N>
inline Raw_Stack<T, N>::Raw_Stack() : _size(0)
{
}

template<class T, size_t N>
inline Raw_Stack<T, N>::Raw_Stack(const Raw_Stack& x)
{
    memcpy(this, &x, sizeof(x));
}

template<class T, size_t N>
inline Raw_Stack<T, N>::~Raw_Stack()
{
}

template<class T, size_t N>
inline Raw_Stack<T, N>& Raw_Stack<T, N>::operator=(const Raw_Stack& x)
{
    if (this != &x)
        memcpy(this, &x, sizeof(x));

    return *this;
}

template<class T, size_t N>
inline size_t Raw_Stack<T, N>::size() const
{
    return _size;
}

template<class T, size_t N>
inline bool Raw_Stack<T, N>::empty() const
{
    return _size == 0;
}

template<class T, size_t N>
inline void Raw_Stack<T, N>::push(const T& x)
{
    CIMPLE_ASSERT(_size != N);
    _rep[_size++] = x;
}

template<class T, size_t N>
inline void Raw_Stack<T, N>::pop()
{
    CIMPLE_ASSERT(_size);
    _size--;
}

template<class T, size_t N>
inline const T& Raw_Stack<T, N>::top() const
{
    CIMPLE_ASSERT(_size);
    return _rep[_size - 1];
}

template<class T, size_t N>
inline T& Raw_Stack<T, N>::top()
{
    CIMPLE_ASSERT(_size);
    return _rep[_size - 1];
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Raw_Stack_h */
