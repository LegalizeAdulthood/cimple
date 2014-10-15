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

#ifndef _cimple_Ref_h
#define _cimple_Ref_h

#include "config.h"
#include "Instance.h"

CIMPLE_NAMESPACE_BEGIN

template<class T>
class Ref
{
public:

    Ref();

    Ref(const Ref& x);

    explicit Ref(T* ptr);

    ~Ref();

    Ref& operator=(const Ref& x);

    const T *operator->() const;

    T *operator->();

    T* ptr();

    const T* ptr() const;

    T& operator*();

    const T& operator*() const;

    T* steal();

    operator bool() const;

    bool operator!() const;

    operator const T*() const;

#if 0
    // Casting constructor.
    template<class U>
    explicit Ref(const Ref<U>& x)
    {
	T* ptr = cast<T*>((U*)x.ptr());

	if (ptr)
	    ref(_ptr = ptr);
	else
	    _ptr = 0;
    }
#endif

private:
    T* _ptr;
};

template<class T>
inline Ref<T>::Ref() : _ptr(0)
{
}

template<class T>
inline Ref<T>::Ref(const Ref<T>& x)
{
    ref(_ptr = x._ptr);
}

template<class T>
inline Ref<T>::Ref(T* ptr) : _ptr(ptr)
{
}

template<class T>
inline Ref<T>::~Ref()
{
    unref(_ptr);
}

template<class T>
Ref<T>& Ref<T>::operator=(const Ref<T>& x)
{
    if (x._ptr != _ptr)
    {
	unref(_ptr);
	ref(_ptr = x._ptr);
    }

    return *this;
}

template<class T>
inline T* Ref<T>::operator->()
{
    return _ptr;
}

template<class T>
inline const T* Ref<T>::operator->() const
{
    return _ptr;
}

template<class T>
inline T* Ref<T>::ptr()
{
    return _ptr;
}

template<class T>
inline const T* Ref<T>::ptr() const
{
    return _ptr;
}

template<class T>
inline T* Ref<T>::steal()
{
    T* tmp = _ptr;
    _ptr = 0;
    return tmp;
}

template<class T>
T& Ref<T>::operator*()
{
    return *_ptr;
}

template<class T>
const T& Ref<T>::operator*() const
{
    return *_ptr;
}

template<class T>
Ref<T>::operator bool() const
{
    return _ptr != 0;
}

template<class T>
bool Ref<T>::operator!() const
{
    return _ptr == 0;
}

template<class T>
Ref<T>::operator const T*() const
{
    return _ptr;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Ref_h */

