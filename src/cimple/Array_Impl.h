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

#ifndef _cimple_Array_Impl
#define _cimple_Array_Impl

#include <cstddef>
#include "config.h"
#include "Type.h"
#include "Atomic.h"

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// struct __Array_Traits
//
//     This structure defines the function table for the Array<> class. It
//     defines pointers to functions that operate on a single array element:
//     construct, destruct, equal.
//
//==============================================================================

struct __Array_Traits
{
    size_t elem_size;
    void (*construct)(void* x, const void* y);
    void (*destruct)(void* x);
    bool (*equal)(const void* x, const void* y);
};

CIMPLE_CIMPLE_LINKAGE
extern const __Array_Traits* __cim_array_traits[];

//==============================================================================
//
// struct __Array_Traits_Factory<>
//
//     This structure is used to build the __Array_Traits object for a generic
//     array element type. Specializations are provided for serveral specific
//     types to improve performance and reduce object size.
//
//==============================================================================

template<class T>
struct __Array_Traits_Factory
{
    static const __Array_Traits* traits()
    {
        static __Array_Traits _traits = 
            { sizeof(T), _construct, _destruct, _equal };
        return &_traits;
    }

private:

    static void _construct(void* x, const void* y)
    {
        new (x) T(*((T*)y));
    }

    static void _destruct(void* x)
    {
        ((T*)x)->~T();
    }

    static bool _equal(const void* x, const void* y)
    {
        return *((T*)x) == *((T*)y);
    }
};

//==============================================================================
//
// struct __Array_Traits_Factory_Raw<T>
//
//     This class is used as a base class for the purposes of specializing
//     __Array_Traits_Factory. The following snippet specializes for boolean.
//
//         template<> struct __Array_Traits_Factory<boolean> : 
//             public __Array_Traits_Factory_Raw<boolean> 
//         { 
//         };
//
//     The __Array_Traits_Factory_Raw produces a traits object for a raw type,
//     which does not require construction, destruction, and comparison. This
//     permits the Array implementation to perform special optimizations. First,
//     it eliminates the need to call a destructor function on each element. 
//     Second, elements may be copied with memcpy() rather than with a special
//     constructor callback. And finally, elements may be compared with memcmp()
//     rather than with a special equal callback.
//
//==============================================================================

template<class T>
struct __Array_Traits_Factory_Raw
{
    static const __Array_Traits* traits()
    {
        static __Array_Traits _traits = { sizeof(T), 0, 0, 0 };
        return &_traits;
    }
};

//==============================================================================
//
// struct __Array_Traits_Factory_CIM<T, N>
//
//==============================================================================

template<class T, int N>
struct __Array_Traits_Factory_CIM
{
    static const __Array_Traits* traits()
    {
        return __cim_array_traits[N];
    }
};

//==============================================================================
//
// __Array_Traits_Factory<boolean> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<boolean> : 
    public __Array_Traits_Factory_CIM<boolean, BOOLEAN> { };

//==============================================================================
//
// __Array_Traits_Factory<uint8> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<uint8> : 
    public __Array_Traits_Factory_CIM<uint8, UINT8> { };

//==============================================================================
//
// __Array_Traits_Factory<sint8> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<sint8> : 
    public __Array_Traits_Factory_CIM<sint8, SINT8> { };

//==============================================================================
//
// __Array_Traits_Factory<uint16> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<uint16> : 
    public __Array_Traits_Factory_CIM<uint16, UINT16> { };

//==============================================================================
//
// __Array_Traits_Factory<sint16> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<sint16> : 
    public __Array_Traits_Factory_CIM<sint16, SINT16> { };

//==============================================================================
//
// __Array_Traits_Factory<uint32> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<uint32> : 
    public __Array_Traits_Factory_CIM<uint32, UINT32> { };

//==============================================================================
//
// __Array_Traits_Factory<sint32> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<sint32> : 
    public __Array_Traits_Factory_CIM<sint32, SINT32> { };

//==============================================================================
//
// __Array_Traits_Factory<uint64> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<uint64> : 
    public __Array_Traits_Factory_CIM<uint64, UINT64> { };

//==============================================================================
//
// __Array_Traits_Factory<real32> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<real32> : 
    public __Array_Traits_Factory_CIM<real32, REAL32> { };

//==============================================================================
//
// __Array_Traits_Factory<real64> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<real64> : 
    public __Array_Traits_Factory_CIM<real64, REAL64> { };

//==============================================================================
//
// __Array_Traits_Factory<sint64> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<sint64> : 
    public __Array_Traits_Factory_CIM<sint64, SINT64> { };

//==============================================================================
//
// __Array_Traits_Factory<char16> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<char16> : 
    public __Array_Traits_Factory_CIM<char16, CHAR16> { };

//==============================================================================
//
// __Array_Traits_Factory<String> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<String> : 
    public __Array_Traits_Factory_CIM<String, STRING> { };

//==============================================================================
//
// __Array_Traits_Factory<datetime> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<Datetime> : 
    public __Array_Traits_Factory_CIM<Datetime, DATETIME> { };

//==============================================================================
//
// __Array_Traits_Factory<void*> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<void*> : 
    public __Array_Traits_Factory_Raw<void*> { };

//==============================================================================
//
// __Array_Traits_Factory<struct Instance*> specialization.
//
//==============================================================================

struct Instance;

template<> struct __Array_Traits_Factory<Instance*> : 
    public __Array_Traits_Factory_Raw<void*> { };

//==============================================================================
//
// __Array_Traits_Factory<struct Meta_Class*> specialization.
//
//==============================================================================

struct Meta_Class;

template<> struct __Array_Traits_Factory<const Meta_Class*> : 
    public __Array_Traits_Factory_Raw<void*> { };

//==============================================================================
//
// __Array_Traits_Factory<struct Instance*> specialization.
//
//==============================================================================

template<> struct __Array_Traits_Factory<const Instance*> : 
    public __Array_Traits_Factory_Raw<void*> { };

//==============================================================================
//
// __Array_Traits_Factory<struct Meta_Class*> specialization.
//
//==============================================================================

struct Meta_Class;

template<> struct __Array_Traits_Factory<Meta_Class*> : 
    public __Array_Traits_Factory_Raw<void*> { };

//==============================================================================
//
// struct __Array_Rep
//
//     This structure represents the internal implementatin of the Array<>
//     class.
//
//==============================================================================

struct __Array_Rep
{
    const __Array_Traits* traits;
    size_t size;
    size_t capacity;
    Atomic refs;
    union
    {
        // Align data suitably for any data type.
        double alignment;
        char data[1];
    };
};

//==============================================================================
//
// Internal Array<> implementation functions.
//
//==============================================================================

CIMPLE_CIMPLE_LINKAGE
void __construct(__Array_Rep*& rep, const __Array_Traits* traits);

CIMPLE_CIMPLE_LINKAGE
void __construct(__Array_Rep*& rep, const __Array_Rep* x);

CIMPLE_CIMPLE_LINKAGE
void __construct(__Array_Rep*& rep, 
    const __Array_Traits* traits, const char* data, size_t size);

CIMPLE_CIMPLE_LINKAGE
void __destruct(__Array_Rep* rep);

CIMPLE_CIMPLE_LINKAGE
void __assign(__Array_Rep*& rep, const __Array_Rep* x);

CIMPLE_CIMPLE_LINKAGE
void __assign(__Array_Rep*& rep, const void* data, size_t size);

CIMPLE_CIMPLE_LINKAGE
void __remove(__Array_Rep*& rep, size_t pos, size_t size);

CIMPLE_CIMPLE_LINKAGE
void __reserve(__Array_Rep*& rep, size_t capacity);

CIMPLE_CIMPLE_LINKAGE
void __resize(__Array_Rep*& rep, size_t size, const void* elem);

CIMPLE_CIMPLE_LINKAGE
void __insert(__Array_Rep*& rep, size_t pos, const void* data, size_t size);

CIMPLE_CIMPLE_LINKAGE
void __append(__Array_Rep*& rep, const void* data, size_t size);

CIMPLE_CIMPLE_LINKAGE
void __prepend(__Array_Rep*& rep, const void* data, size_t size);

CIMPLE_CIMPLE_LINKAGE
bool __equal(const __Array_Rep* x, const __Array_Rep* y);

CIMPLE_CIMPLE_LINKAGE
size_t __find(const __Array_Rep* rep, const void* elem);

inline const char* __at(const __Array_Rep* rep, size_t pos)
{
    return rep->data + (rep->traits->elem_size * pos);
}

//==============================================================================
//
// struct __Array_Base
//
//     This structure has the same alignment and members as the Array<> class.
//     It is used to avoid making friends of all functions that access the
//     internal _rep member. Simply cast Array<> to __Array_Base to gain access
//     to its rep member.
//
//==============================================================================

struct __Array_Base
{
    __Array_Rep* rep;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Array_Impl */
