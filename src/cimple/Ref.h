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
/**
    The Ref class is a smart pointer template that uses
    reference counting to manage the lifetime of instances.
    
    A Ref object is created with:
   
        Ref<Class>
  
    \verbatim
    Example:
       // Create a ref of an an instance, a smart pointer form of the
       // instance inst that will be destroyed when inst goes out of
       // scope
       Ref<Instance> inst;

       ... put data into the inst

       // cast the inst to the CIMPLE CIM_ComputerSystem class
       CIM_ComputerSystem* ccs  = cast<CIM_ComputerSystem*>(inst.ptr());
    \endverbatim

    This class contains methods for:
        \li construction (Ref),
        \li unreferencing (#reset) that either returns the
          pointer to the object or sets it to zero,
        \li #ptr which returns the pointer to the entity,
        \li #steal returns a pointer to the entity and sets the
         internal pointer to zero,
        \li #count that returns the count of the number of
         references,
        \li booleans to determine if the pointer is zero or not.

    The methods are implemented as inline code within this header file for
    efficiency.
*/
template<class T>
class Ref
{
public:

    /// constructor
    Ref();

    ///
    Ref(const Ref<T>& x)
    {
        ref(_ptr = x._ptr);
    }

    /** 
     * Construct a reference for the class and cast the 
     * pointer to this class 
     * 
     * @tparam U
     * @param ptr
     */
    template<class U>
    Ref(U* ptr)
    {
        _ptr = cast<T*>(ptr);
    }

    /// destructor
    ~Ref();

    /// Assign a Ref
    Ref& operator=(const Ref& x);

    /** 
     * unreference instance; set pointer to zero
     */
    void reset();

    /** 
     * unreference instance and set pointer to ptr argument
     * @param ptr
     */
    void reset(T* ptr);

    ///
    const T *operator->() const;

    ///
    T *operator->();

    /** 
     * return pointer to the Ref'd entity
     * @return T* 
     *      * \verbatim
     * Example:
     *     Ref<Instance> x(X::create(true));
     *     Instance* y = x.ptr();
     * \endverbatim  
     */
    T* ptr();

    /** 
     * Return const pointer to the Ref'd entity
     * 
     * @return const T* 
     * \verbatim
     * Example:
     *     Ref<Instance> x(X::create(true));
     *     const Instance* y = x.ptr();
     * \endverbatim  
     */
    const T* ptr() const;

    ///
    T& operator*();

    ///
    const T& operator*() const;

    /** 
     * return pointer to instance; set pointer to zero. Once you 
     * steal a Ref, it is your problem to destroy it. 
     * @return T* 
     * \verbatim
     * Example:
     *     Ref<Instance> x(X::create(true));
     *     Instance* x.steal();
     * \endverbatim 
     */
    T* steal();

    ///
    operator bool() const;

    ///
    bool operator!() const;

    /** 
     * return current reference count
     * @return size_t Current reference count 
     * \verbatim
     * Example:
     *     Ref<Instance> x(X::create(true));
     *     printf("count = %zd\n", x.count());
     * \endverbatim
     */
    size_t count() const;

private:
    T* _ptr;
};

// inline implementations of the Ref methods

template<class T>
inline Ref<T>::Ref() : _ptr(0)
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
inline void Ref<T>::reset()
{
    unref(_ptr);
    _ptr = 0;
}

template<class T>
inline void Ref<T>::reset(T* ptr)
{
    unref(_ptr);
    ref(_ptr = ptr);
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
inline T& Ref<T>::operator*()
{
    return *_ptr;
}

template<class T>
inline const T& Ref<T>::operator*() const
{
    return *_ptr;
}

template<class T>
inline Ref<T>::operator bool() const
{
    return _ptr != 0;
}

template<class T>
inline bool Ref<T>::operator!() const
{
    return _ptr == 0;
}

template<class T>
size_t Ref<T>::count() const
{
    return Atomic_get(&_ptr->__refs);
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_Ref_h */
