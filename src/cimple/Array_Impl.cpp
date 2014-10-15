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

#include "Array_Impl.h"

CIMPLE_NAMESPACE_BEGIN

static const size_t _MIN_CAPACITY = 8;

//==============================================================================
//
// __Array_Traits_Factory<String>
//
//==============================================================================

static void _String_construct(void* x, const void* y)
{
    new (x) String(*((String*)y));
}

static void _String_destruct(void* x)
{
    ((String*)x)->~String();
}

static bool _String_equal(const void* x, const void* y)
{
    return *((String*)x) == *((String*)y);
}

__Array_Traits* __Array_Traits_Factory<String>::traits()
{
    static __Array_Traits _traits = 
	{ sizeof(String), _String_construct, _String_destruct, _String_equal };

    return &_traits;
}

//==============================================================================
//
// __Array_Traits_Factory<real32>
//
//==============================================================================

static bool _real32_equal(const void* x, const void* y)
{
    return *((real32*)x) == *((real32*)y);
}

__Array_Traits* __Array_Traits_Factory<real32>::traits()
{
    static __Array_Traits _traits = { sizeof(real32), 0, 0, _real32_equal };
    return &_traits;
}

//==============================================================================
//
// __Array_Traits_Factory<real64>
//
//==============================================================================

static bool _real64_equal(const void* x, const void* y)
{
    return *((real64*)x) == *((real64*)y);
}

__Array_Traits* __Array_Traits_Factory<real64>::traits()
{
    static __Array_Traits _traits = { sizeof(real32), 0, 0, _real64_equal };
    return &_traits;
}

//==============================================================================
//
// Internal Array<> implementation functions.
//
//==============================================================================

static inline __Array_Rep* _allocate(__Array_Traits* traits, size_t capacity)
{
    return (__Array_Rep*)malloc(
	sizeof(__Array_Rep) + (traits->elem_size * capacity));
}

static void _copy(__Array_Rep* rep, char* p, const char* q, size_t size)
{
    size_t elem_size = rep->traits->elem_size;
    size_t nbytes = size * elem_size;

    if (rep->traits && rep->traits->construct)
    {
	const char* end = p + nbytes;

	for (; p != end; p += elem_size, q += elem_size)
	    rep->traits->construct(p, q);
    }
    else
	memcpy(p, q, nbytes);
}

static void _destroy(__Array_Rep* rep, char* data, size_t size)
{
    if (rep->traits && rep->traits->destruct)
    {
	for (size_t i = 0; i < size; i++, data += rep->traits->elem_size)
	    rep->traits->destruct(data);
    }
}

static void _fill(__Array_Rep* rep, char* p, size_t size, const void* elem)
{
    size_t elem_size = rep->traits->elem_size;
    size_t nbytes = size * elem_size;

    if (rep->traits && rep->traits->construct)
    {
	const char* end = p + nbytes;

	for (; p != end; p += elem_size)
	    rep->traits->construct(p, elem);
    }
    else
	memset(p, 0, nbytes);
}

static void _release(__Array_Rep* rep)
{
    _destroy(rep, rep->data, rep->size);
    free(rep);
}

static __Array_Rep* _clone(
    __Array_Traits* traits,
    const char* data, 
    size_t size)
{
    __Array_Rep* rep = _allocate(traits, size);
    rep->traits = traits;
    rep->traits->elem_size = traits->elem_size;
    rep->size = size;
    rep->capacity = size;
    _copy(rep, rep->data, data, size);

    return rep;
}

void __construct(__Array_Rep*& rep, __Array_Traits* traits)
{
    rep = _allocate(traits, _MIN_CAPACITY);
    rep->traits = traits;
    rep->traits->elem_size = traits->elem_size;
    rep->size = 0;
    rep->capacity = _MIN_CAPACITY;
}

void __construct(__Array_Rep*& rep, const __Array_Rep* x)
{
    rep = _clone(x->traits, x->data, x->size);
}

void __construct(
    __Array_Rep*& rep, 
    __Array_Traits* traits,
    const char* data, 
    size_t size)
{
    rep = _clone(traits, data, size);
}

void __destruct(__Array_Rep* rep)
{
    _release(rep);
}

void __assign(__Array_Rep*& rep, const __Array_Rep* x)
{
    _release(rep);
    rep = _clone(x->traits, x->data, x->size);
}

void __reserve(__Array_Rep*& rep, size_t capacity)
{
    if (capacity > rep->capacity)
    {
	size_t r = _MIN_CAPACITY;

	while (r < capacity)
	    r <<= 1;

	rep = (__Array_Rep*)realloc(
	    rep, sizeof(__Array_Rep) + (rep->traits->elem_size * capacity));

	rep->capacity = capacity;
    }
}

void __resize(__Array_Rep*& rep, size_t size, const void* elem)
{
    ssize_t diff = size - rep->size;

    if (diff > 0)
    {
	__reserve(rep, size);
	_fill(rep, 
	    rep->data + (rep->size * rep->traits->elem_size), diff, elem);
    }
    else if (diff < 0)
	_destroy(rep, rep->data + (size * rep->traits->elem_size), -diff);

    rep->size = size;
}

void __assign(__Array_Rep*& rep, const void* data, size_t size)
{
    __Array_Traits* traits = rep->traits;
    _release(rep);
    rep = _clone(traits, (const char*)data, size);
}

void __insert(__Array_Rep*& rep, size_t pos, const void* data, size_t size)
{
    // assert(pos > rep->size);
    // assert(size != (size_t)-1);

    __reserve(rep, rep->size + size);
    size_t elem_size = rep->traits->elem_size;
    char* ptr = (char*)(rep->data + pos * elem_size);
    memmove(
	rep->data + (pos + size) * elem_size, 
	ptr, 
	(rep->size - pos) * elem_size);
    _copy(rep, ptr, (char*)data, size);
    rep->size += size;
}

void __append(__Array_Rep*& rep, const void* data, size_t size)
{
    __insert(rep, rep->size, data, size);
}

void __prepend(__Array_Rep*& rep, const void* data, size_t size)
{
    __insert(rep, 0, data, size);
}

void __remove(__Array_Rep*& rep, size_t pos, size_t size)
{
    // assert(pos + size <= rep->size);

    size_t elem_size = rep->traits->elem_size;
    char* ptr = rep->data + pos * elem_size;
    _destroy(rep, ptr, size);
    memmove(
	ptr, 
	rep->data + (pos + size) * elem_size, 
	(rep->size - (pos + size)) * elem_size);
    rep->size -= size;
}

bool __equal(const __Array_Rep* rep, const __Array_Rep* x)
{
    if (rep->size != x->size)
	return false;

    if (rep->traits && rep->traits->equal)
    {
	for (size_t i = 0; i < rep->size; i++)
	{
	    size_t offset = rep->traits->elem_size * i;

	    if (!rep->traits->equal(rep->data + offset, x->data + offset))
		return false;
	}

	return true;
    }
    else
	return memcmp(rep->data, x->data, rep->traits->elem_size * rep->size) == 0;
}

size_t __find(const __Array_Rep* rep, const void* elem)
{
    for (size_t i = 0; i < rep->size; i++)
    {
	const char* tmp_elem = rep->data + (rep->traits->elem_size * i);

	if (rep->traits && rep->traits->equal)
	{
	    if (rep->traits->equal(tmp_elem, elem))
		return i;
	}
	else
	{
	    if (memcmp(tmp_elem, elem, rep->traits->elem_size) == 0)
		return true;
	}
    }

    // Not found!
    return size_t(-1);
}

CIMPLE_NAMESPACE_END
