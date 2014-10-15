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

#ifndef _cimple_Property_h
#define _cimple_Property_h

#include "config.h"
#include "Type.h"

CIMPLE_NAMESPACE_BEGIN

/** Implements a simple property as used within the generated classes. It
    holds a value (whose type is given by the template argument) and a null
    flag. The null flag indicates that a value is not present.
*/
template<class T>
struct Property
{
    T value;
    uint8 null;

    void set(const T& x);
    void clear();
};

template<class T>
inline void Property<T>::set(const T& x)
{
    value = x;
    null = false;
}

template<class T>
inline void Property<T>::clear()
{
    __clear(value); 
    null = true;
}

template<class T>
inline bool operator==(const Property<T>& x, const Property<T>& y)
{
    return x.null == y.null && x.value == y.value;
}

template<class T>
inline bool operator!=(const Property<T>& x, const Property<T>& y)
{
    return !operator==(x, y);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Property_h */
