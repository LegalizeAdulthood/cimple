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

#ifndef _cimple_Array_h
#define _cimple_Array_h

#include <cstddef>
#include "config.h"
#include "Type.h"

CIMPLE_NAMESPACE_BEGIN

typedef void (*Ctor_Proc)(void* to, const void* from);
typedef void (*Dtor_Proc)(void* ptr);
typedef bool (*Equal_Proc)(const void* ptr1, const void* ptr2);

struct Instance;
struct Meta_Class;
struct Meta_Property;

class CIMPLE_LIBCIMPLE_LINKAGE Array_Base
{
public:

    void reserve(size_t cap);

    size_t size() const 
    {
	return _size; 
    }

    const void* get_raw(size_t i) const
    {
	return _data + (_esize * _size);
    }

    void append_raw(const void* data, size_t size)
    {
	_append(data, size);
    }

protected:

    Array_Base(size_t esize);

    Array_Base(size_t esize, Ctor_Proc ctor, Dtor_Proc dtor);

    Array_Base(size_t esize, const void* data, size_t size);

    Array_Base(size_t esize, 
	Ctor_Proc ctor, Dtor_Proc dtor, const void* data, size_t size);

    Array_Base(const Array_Base& x);

    ~Array_Base();

    void _resize(size_t size, const void* elem);

    void _assign(const Array_Base& x);

    void _assign(const void* data, size_t size);

    void _swap(Array_Base& x);

    void _insert(size_t pos, const void* data, size_t size);

    void _append(const void* data, size_t size);

    void _prepend(const void* data, size_t size);

    void _remove(size_t pos, size_t size);

    Array_Base& operator=(const Array_Base& x) 
    {
	_assign(x);
	return *this; 
    }

    void _release();

    void _assign_no_release(const char* data, size_t size);

    void _destroy(char* data, size_t size);

    void _copy(char* p, const char* q, size_t size);

    void _fill(char* p, size_t size, const void* elem);

    void _construct(size_t esize, 
	Ctor_Proc ctor, Dtor_Proc dtor, const void* data, size_t size);

    size_t _esize;
    Ctor_Proc _ctor;
    Dtor_Proc _dtor;

    char* _data;
    size_t _size;
    size_t _cap;

    friend void __construct(const Meta_Class*, Instance*);
    friend void __destruct(Instance* instance);
    friend void __uninitialized_copy(Instance*, const Instance*);
    friend struct IO;
    friend void __copy(Instance*, const Instance*, bool);

    CIMPLE_LIBCIMPLE_LINKAGE
    friend void copy_keys(Instance*, const Instance*);

    friend void _random_property_initialize(const Meta_Property*, void*);
    friend class Facade;

    friend bool __equal(const Array_Base&, const Array_Base&);
    friend bool __equal(const Array_Base&, const Array_Base&, Equal_Proc);
};

bool __equal(const Array_Base& x, const Array_Base& y);
bool __equal(const Array_Base& x, const Array_Base& y, Equal_Proc equal);

template<class T>
class Array : public Array_Base
{
public:

    Array() : Array_Base(sizeof(T), _ctor, _dtor) 
    {
    }

    Array(const T* data, size_t size) : Array_Base(sizeof(T), data, size) 
    {
    }

    Array(const Array& x) : Array_Base(x) 
    {
    }

    Array<T>& operator=(const Array<T>& x)
    {
	_assign(x);
	return *this;
    }

    void clear()
    {
	remove(0, _size);
    }

    size_t capacity() const 
    { 
	return _cap; 
    }

    const T* data() const 
    { 
	return (T*)_data; 
    }

    T* data() 
    { 
	return (T*)_data; 
    }

    T& operator[](size_t pos) 
    { 
	return ((T*)_data)[pos]; 
    }

    const T& operator[](size_t pos) const 
    { 
	return ((T*)_data)[pos]; 
    }

#if 0
    void reserve(size_t cap) 
    { 
	_reserve(cap); 
    }
#endif

    void resize(size_t size) 
    {
	static T x;
	_resize(size, &x); 
    }

    void assign(const Array& x) 
    { 
	_assign(x); 
    }

    void assign(const T* data, size_t size) 
    {
	_assign(data, size); 
    }

    void swap(Array& x) 
    { 
	_swap(x); 
    }

    void insert(size_t pos, const T* data, size_t size)
    {
	_insert(pos, data, size);
    }

    void insert(size_t pos, const T& elem)
    {
	_insert(pos, &elem, 1);
    }

    void append(const T* data, size_t size)
    {
	_append(data, size);
    }

    void append(const T& elem)
    {
	_append(&elem, 1);
    }

    void prepend(const T* data, size_t size)
    {
	_prepend(data, size);
    }

    void prepend(const T& elem)
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

private:

    static void _ctor(void* x, const void* y) 
    {
	new(x) T(*((T*)y)); 
    }

    static void _dtor(void* x) 
    { 
	((T*)x)->~T(); 
    }
};

template<class T>
struct Equal
{
    static bool proc(const void* x, const void* y)
    {
	return *((T*)x) == *((T*)y);
    }
};

template<>
struct Equal<String>
{
    static bool proc(const void* x, const void* y);
};

template<>
struct Equal<real32>
{
    static bool proc(const void* x, const void* y);
};

template<>
struct Equal<real64>
{
    static bool proc(const void* x, const void* y);
};

template<class T>
bool operator==(const Array<T>& x, const Array<T>& y)
{
    return __equal(x, y, Equal<T>::proc);
}

template<class T> 
inline void clear(Array<T>& x) 
{ 
    x.clear(); 
}

#define CIMPLE_T boolean
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T uint8
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T sint8
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T uint16
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T sint16
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T uint32
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T sint32
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T uint64
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T sint64
#include "Array_Special.h"
#include "Array_Equal.h"
#undef CIMPLE_T

#define CIMPLE_T real32
#include "Array_Special.h"
#undef CIMPLE_T

#define CIMPLE_T real64
#include "Array_Special.h"
#undef CIMPLE_T

#define CIMPLE_T Datetime
#include "Array_Special.h"
#undef CIMPLE_T

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

CIMPLE_NAMESPACE_END

#endif /* _cimple_Array_h */
