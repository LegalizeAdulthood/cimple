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

#ifndef _cimple_Array_h
#define _cimple_Array_h

#include "config.h"
#include "Array_Impl.h"

CIMPLE_NAMESPACE_BEGIN

/** The #Array# class manages a sequence of elements located on the heap. 

    \section section1 Introduction

    The #Array class has functions for inserting, accessing, and removing 
    elements. This class is similar to the STL #vector class but offers three 
    major advantages.

        - It causes virtually no code bloat due to template usage.
        - It offers binary compatibility from one release to the next.
        - It provides a simplified index-oriented interface (no iterators).

    The snippet below creates an array with three integers.

    \code
    Array<int> a;
    a.append(1);
    a.append(2);
    a.append(3);
    \endcode

    Continuing with this example, the following snippet prints the contents
    of the array we just built.

    \code
    for (size_t i = 0; i < a.size(); i++)
        printf("%d\n", a[i]);
    \endcode

    Arrays can also be used to manage sequences of class objects. For example,
    the following snippet builds an array with three String objects.

    \code
    Array<String> a;
    a.append("apple");
    a.append("orange");
    a.append("banana");
    \endcode

    \section section2 Inserting Elements

    The following functions are used to add elements to an array.

        - #insert()
        - #prepend()
        - #append()

    Prepend() adds elements to the beginning of the array and append() adds
    them to the end. Insert() adds elements at a given position. The example
    below builds an array with two elements and then inserts an element in 
    the middle.

    \code
    Array<int> a;
    a.append(200);
    a.prepend(100);
    a.insert(1, 300);
    \endcode

    There are also forms of these three functions for adding more than one 
    element as shown below.

    \code
    Array<int> a;
    int elements[] = { 10, 20, 30, 40, 50 };
    a.append(elements, 5);
    \endcode

    \section section3 Removing Elements

    The #Array class provides two methods for removing elements from an array:
    one that removes a single element and one that removes one or more elements.
    The following snippet illustrates both.

    \code
    Array<int> a;
    a.append(0);
    a.append(1);
    a.append(2);
    a.append(3);
    a.append(4);

    // Remove first element:
    a.remove(0);

    // Remove last element:
    a.remove(a.size()-1);

    // Remove last two elements.
    a.remove(1, 2);
    \endcode


    \section section4 Clearing an Array

    The clear() function removes all elements from an array. After calling 
    clear(), the size() function will return zero. But clearing an array does
    not necessarily reclaim any memory used by the array. The memory is 
    retained to reduce overhead associated with any future insertions. To
    reclaim the memory, the array itself must be destructed.

    \section section5 Reserving Memory

    The #Array class automatically expands the internal memory allocation as
    elements are added. Extra space may be reserved for future additions to
    limit resource usage. For example, an array with five elements may have
    space for as many as eight. In general, allocations are rounded up
    to the next power of two. Like STL vectors, the #Array class provides
    a reserve() function that makes space for so many elements. But note that
    reserve() does not change the size of the array. If you know you are about
    to create an array with 100 elements, it will reduce allocation and copying
    by reserving the memory up front. The following snippet will incur at most
    one allocation.

    \code
    Array<uint32> a;
    a.reserve(100);

    for (size_t i = 0; i < 100; i++)
        a.append(i);
    \endcode

    \section section6 Error Checking

    The #Array class (like the functions in the standard C library) performs
    no error checking on input arguments. For example, passing a null pointer 
    to a member function will result in a crash. Similary, passing an 
    out-of-range index will have unpredictable results. It is the caller's 
    responsibility to avoid these errors. Explict error checking would make 
    the implementation bigger and slower, which is mainly why the C library 
    routines do not check for errors either. For example, the following use 
    of strcpy() will surely cause a crash.

    \code
    // core dump!
    strcpy(NULL, NULL);
    \endcode
*/
template<class T>
class Array
{
public:

    /** Default constructor.
    */
    Array();

    /** Copy constructor.
    */
    Array(const Array& x);

    /** Initializes an array with size elements.
    */
    Array(const T* data, size_t size);

    /** Destructor
    */
    ~Array();

    /** Assignment operator.
    */
    Array<T>& operator=(const Array<T>& x);

    /** Assignment.
    */
    void assign(const Array& x);

    /** Assigns size elements to the array.
    */
    void assign(const T* data, size_t size);

    /** Returns the number of elements in the array.
    */
    size_t size() const;

    /** Returns the number of elements the array has room for. The following
        invariant is always true: capacity() >= size().
    */
    size_t capacity() const;

    /** Returns a pointer to the first element in the array (const form).
    */
    const T* data() const;

    /** Returns a pointer to the last element in the array.
    */
    T* data();

    /** Index operator for obtaining the i-th element of the array.
    */
    T& operator[](size_t pos);

    /** Index operator for obtaining the i-th element of the array (const form).
    */
    const T& operator[](size_t pos) const;

    /** Increases the internal allocation to accomodate the given
    *   number of elements if capacity is greater than capacity().
    *   Note that this function has no effect on the size() of the
    *   array.
    */
    void reserve(size_t capacity);

    /** Change the size of the array. If size is less than size(), elements are
        removed. If size() is greater than size(), then new elements are added.
        Upon return, size() is the same as size.
    */
    void resize(size_t size);

    /** Insert size elements at the given position.
    */
    void insert(size_t pos, const T* data, size_t size);

    /** Insert one element at the given position.
    */
    void insert(size_t pos, const T& elem);

    /** Append size elements to the end of the arrray.
    */
    void append(const T* data, size_t size);

    /** Append one element to the end of the array.
    */
    void append(const T& elem);

    /** Prepend size elements to the beginning of the array.
    */
    void prepend(const T* data, size_t size);

    /** Prepend one element to the beginning of the array.
    */
    void prepend(const T& elem);

    /** Remove size elements from the array starting at the given position.
    */
    void remove(size_t pos, size_t size);

    /** Remove one element from the array at the given position.
    */
    void remove(size_t pos);

    /** Remove all elements. This function does not change the capacity.
    */
    void clear();

    /** Swaps the internal implementation of this array with another array.
    */
    void swap(Array& x);

    /** Attempts to find the an element that is equal to x.
        @return position matching element or size_t(-1) if not found.
    */
    size_t find(const T& x) const;

    /** Make an array with one element.
    */
    static Array<T> make(const T& x0);

    /** Make an array with two elements.
    */
    static Array<T> make(const T& x0, const T& x1);

    /** Make an array with three elements.
    */
    static Array<T> make(const T& x0, const T& x1, const T& x2);

    /** Make an array with four elements.
    */
    static Array<T> make(const T& x0, const T& x1, const T& x2, 
        const T& x3);

    /** Make an array with five elements.
    */
    static Array<T> make(const T& x0, const T& x1, const T& x2, 
        const T& x3, const T& x4);

private:

    __Array_Rep* _rep;
};

template<class T>
inline Array<T>::Array() 
{
    __construct(_rep, __Array_Traits_Factory<T>::traits());
}

template<class T>
inline Array<T>::Array(const Array& x)
{
    __construct(_rep, x._rep);
}

template<class T>
inline Array<T>::Array(const T* data, size_t size)
{
    __construct(
        _rep, __Array_Traits_Factory<T>::traits(), (const char*)data, size);
}

template<class T>
inline Array<T>::~Array()
{
    __destruct(_rep);
}

template<class T>
inline Array<T>& Array<T>::operator=(const Array<T>& x)
{
    __assign(_rep, x._rep);
    return *this;
}

template<class T>
inline void Array<T>::assign(const Array& x) 
{ 
    __assign(_rep, x); 
}

template<class T>
inline void Array<T>::assign(const T* data, size_t size) 
{
    __assign(_rep, data, size); 
}

template<class T>
inline size_t Array<T>::size() const 
{
    return _rep->size;
}

template<class T>
inline size_t Array<T>::capacity() const 
{
    return _rep->capacity;
}

template<class T>
inline const T* Array<T>::data() const 
{ 
    return (const T*)_rep->data;
}

template<class T>
inline T* Array<T>::data() 
{ 
    return (T*)_rep->data;
}

template<class T>
inline T& Array<T>::operator[](size_t pos) 
{
    return data()[pos];
}

template<class T>
inline const T& Array<T>::operator[](size_t pos) const 
{
    return data()[pos];
}

template<class T>
inline void Array<T>::reserve(size_t capacity) 
{
    __reserve(_rep, capacity); 
}

template<class T>
inline void Array<T>::resize(size_t size) 
{
    static T x;
    __resize(_rep, size, &x); 
}

template<class T>
inline void Array<T>::insert(size_t pos, const T* data, size_t size)
{
    __insert(_rep, pos, data, size);
}

template<class T>
inline void Array<T>::insert(size_t pos, const T& elem)
{
    __insert(_rep, pos, &elem, 1);
}

template<class T>
inline void Array<T>::append(const T* data, size_t size)
{
    __append(_rep, data, size);
}

template<class T>
inline void Array<T>::append(const T& elem)
{
    __append(_rep, &elem, 1);
}

template<class T>
inline void Array<T>::prepend(const T* data, size_t size)
{
    __prepend(_rep, data, size);
}

template<class T>
inline void Array<T>::prepend(const T& elem)
{
    __prepend(_rep, &elem, 1);
}

template<class T>
inline void Array<T>::remove(size_t pos, size_t size)
{
    __remove(_rep, pos, size);
}

template<class T>
inline void Array<T>::remove(size_t pos)
{
    __remove(_rep, pos, 1);
}

template<class T>
inline void Array<T>::clear()
{
    __remove(_rep, 0, _rep->size);
}

template<class T>
inline void Array<T>::swap(Array& x) 
{
    __Array_Rep* tmp = _rep;
    _rep = x._rep;
    x._rep = tmp;
}

template<class T>
inline size_t Array<T>::find(const T& x) const
{
    return __find(_rep, &x);
}

template<class T>
inline Array<T> Array<T>::make(const T& x0)
{
    Array<T> a;
    a.append(x0);
    return a;
}

template<class T>
inline Array<T> Array<T>::make(const T& x0, const T& x1)
{
    Array<T> a;
    a.append(x0);
    a.append(x1);
    return a;
}

template<class T>
inline Array<T> Array<T>::make(const T& x0, const T& x1, const T& x2)
{
    Array<T> a;
    a.append(x0);
    a.append(x1);
    a.append(x2);
    return a;
}

template<class T>
inline Array<T> Array<T>::make(
    const T& x0, 
    const T& x1, 
    const T& x2,
    const T& x3)
{
    Array<T> a;
    a.append(x0);
    a.append(x1);
    a.append(x2);
    a.append(x3);
    return a;
}

template<class T>
inline Array<T> Array<T>::make(
    const T& x0, 
    const T& x1, 
    const T& x2,
    const T& x3,
    const T& x4)
{
    Array<T> a;
    a.append(x0);
    a.append(x1);
    a.append(x2);
    a.append(x3);
    a.append(x4);
    return a;
}

template<class T>
inline bool operator==(const Array<T>& x, const Array<T>& y)
{
    return __equal(((__Array_Base*)&x)->rep, ((__Array_Base*)&y)->rep);
}

template<class T>
inline void __clear(Array<T>& x)
{
    x.clear();
}

typedef Array<cimple::boolean> Array_boolean;
typedef Array<cimple::uint8> Array_uint8;
typedef Array<cimple::sint8> Array_sint8;
typedef Array<cimple::uint16> Array_uint16;
typedef Array<cimple::sint16> Array_sint16;
typedef Array<cimple::uint32> Array_uint32;
typedef Array<cimple::sint32> Array_sint32;
typedef Array<cimple::uint64> Array_uint64;
typedef Array<cimple::sint64> Array_sint64;
typedef Array<cimple::real32> Array_real32;
typedef Array<cimple::real64> Array_real64;
typedef Array<cimple::char16> Array_char16;
typedef Array<cimple::String> Array_String;
typedef Array<cimple::Datetime> Array_Datetime;
typedef Array<cimple::Instance*> Array_Instance;
typedef Array<cimple::Instance*> Array_Ref;

CIMPLE_NAMESPACE_END

#endif /* _cimple_Array_h */
