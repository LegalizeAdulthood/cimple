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

#ifndef _cimple_Property_Ref_h
#define _cimple_Property_Ref_h

#include "config.h"
#include "Property.h"

CIMPLE_NAMESPACE_BEGIN

template<class T>
class Property_Ref
{
public:

    typedef Property<T> P;
    typedef Property_Ref<T> Self;

    Property_Ref(P* ptr);
    Property_Ref();
    void set(const T& x);
    void clear();
    const T& get() const;
    bool null() const;

    //operator const T&() const { return _ptr->value; }

private:

    Property_Ref(const Property_Ref& x);
    Property_Ref& operator=(const Property_Ref& x) { return *this; }
    P* _ptr;
};

template<class T>
inline Property_Ref<T>::Property_Ref(P* ptr) : _ptr(ptr) 
{ 
}

template<class T>
inline Property_Ref<T>::Property_Ref() 
{ 
}

template<class T>
void Property_Ref<T>::set(const T& x) 
{
    _ptr->value = x; 
    _ptr->null = false; 
}

template<class T>
void Property_Ref<T>::clear()
{
    _ptr->null = true;  
    cimple::clear(_ptr->value); 
}

template<class T>
inline const T& Property_Ref<T>::get() const 
{ 
    return _ptr->value; 
}

template<class T>
inline bool Property_Ref<T>::null() const 
{ 
    return _ptr->null; 
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Property_Ref_h */
