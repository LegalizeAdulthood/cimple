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

#ifndef _cimple_Arg_h
#define _cimple_Arg_h

#include "config.h"
#include "Value.h"

CIMPLE_NAMESPACE_BEGIN

template<class T>
class Arg
{
public:

    Arg();

    Arg(const T& x);

    ~Arg();

    Arg& operator=(const Arg& x);

    void value(const T& x);

    const T& value() const;

    bool null() const;

    void clear();

private:

    T _value;
    bool _null;
};

template<class T>
inline Arg<T>::Arg() : _null(true) 
{ 
}

template<class T>
inline Arg<T>::Arg(const T& x) : _value(x), _null(false) 
{
}

template<class T>
inline Arg<T>::~Arg()
{
}


template<class T>
inline Arg<T>& Arg<T>::operator=(const Arg& x)
{
    if (this != &x)
    {
        _value = x._value;
        _null = x._null;
    }

    return *this;
}

template<class T>
inline void Arg<T>::value(const T& x)
{
    _value = x;
    _null = false;
}

template<class T>
inline const T& Arg<T>::value() const
{
    return _value;
}

template<class T>
inline bool Arg<T>::null() const
{
    return _null;
}

template<class T>
inline void Arg<T>::clear()
{
    __clear(_value);
    _null = true;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Arg_h */
