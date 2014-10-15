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

#ifndef _cimple_Statck_h
#define _cimple_Statck_h

#include "config.h"
#include "Array.h"

CIMPLE_NAMESPACE_BEGIN

/** 
 * Stack Class implemented as a template.  The implementation 
 * for this class is inline.
 * 
 */
template<class T>
class Stack
{
public:

    ///
    Stack();

    ///
    Stack(const Stack& x);

    ///
    ~Stack();

    ///
    Stack& operator=(const Stack& x);

    ///
    size_t size() const;

    ///
    bool empty() const;

    ///
    void push(const T& x);

    ///
    void pop();

    ///
    const T& top() const;

    ///
    T& top();

private:
    Array<T> _rep;
};

template<class T>
inline Stack<T>::Stack()
{
}

template<class T>
inline Stack<T>::Stack(const Stack& x) : _rep(x._rep)
{
}

template<class T>
inline Stack<T>::~Stack()
{
}

template<class T>
inline Stack<T>& Stack<T>::operator=(const Stack& x)
{
    _rep = x._rep;
    return *this;
}

template<class T>
inline size_t Stack<T>::size() const
{
    return _rep.size();
}

template<class T>
inline bool Stack<T>::empty() const
{
    return _rep.size() == 0;
}

template<class T>
inline void Stack<T>::push(const T& x)
{
    _rep.append(x);
}

template<class T>
inline void Stack<T>::pop()
{
    CIMPLE_ASSERT(_rep.size() > 0);
    _rep.remove(_rep.size()-1);
}

template<class T>
inline const T& Stack<T>::top() const
{
    CIMPLE_ASSERT(_rep.size() > 0);
    return _rep[_rep.size() - 1];
}

template<class T>
inline T& Stack<T>::top()
{
    CIMPLE_ASSERT(_rep.size() > 0);
    return _rep[_rep.size() - 1];
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Statck_h */
