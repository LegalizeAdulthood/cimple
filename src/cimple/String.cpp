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

#include <cassert>
#include <cstdlib>
#include "String.h"
#include "flags.h"

CIMPLE_NAMESPACE_BEGIN

static const uint32 INITIAL_STRING_SIZE = 16;

String::Rep String::_empty;

static inline uint32 _next_pow_2(uint32 x)
{
    if (x < INITIAL_STRING_SIZE)
	return INITIAL_STRING_SIZE;

    x--;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x++;

    return x;
}

String::Rep* String::_new(size_t cap) 
{
    cap = _next_pow_2(cap);
    Rep* rep = (Rep*)::operator new(sizeof(Rep) + cap);
    rep->cap = cap;
    Atomic_create(&rep->refs, 1);
    return rep;
}

void String::_append_char(char c)
{
    Rep* rep;

    if (_rep->cap)
    {
        rep = _new(2 * _rep->cap);
        rep->size = _rep->size;
	memcpy(rep->data, _rep->data, _rep->size);
    }
    else
    {
        rep = _new(INITIAL_STRING_SIZE);
        rep->size = 0;
    }

    _unref(_rep);
    _rep = rep;
}

String::String(const char* s)
{
    if (*s)
    {
	size_t n = strlen(s);
	_rep = _new(n);
	memcpy(_rep->data, s, n + 1);
	_rep->size = n;
    }
    else
	_rep = &_empty;
}

String::String(const char* s, size_t n)
{
    if (n)
    {
	_rep = _new(n);
	memcpy(_rep->data, s, n);
	_rep->data[n] = '\0';
	_rep->size = n;
    }
    else
	_rep = &_empty;
}

String::String(const char* s1, const char* s2)
{
    size_t n1 = strlen(s1);
    size_t n2 = strlen(s2);
    size_t n = n1 + n2;
    _rep = _new(n);
    memcpy(_rep->data, s1, n1);
    memcpy(_rep->data + n1, s2, n2);
    _rep->data[n] = '\0';
}

String::String(const char* s1, const char* s2, const char* s3)
{
    size_t n1 = strlen(s1);
    size_t n2 = strlen(s2);
    size_t n3 = strlen(s3);
    size_t n = n1 + n2 + n3;
    _rep = _new(n);
    memcpy(_rep->data, s1, n1);
    memcpy(_rep->data + n1, s2, n2);
    memcpy(_rep->data + n1 + n2, s3, n3);
    _rep->data[n] = '\0';
}

void String::_reserve(size_t n)
{
    Rep* new_rep = _new(n);
    new_rep->size = _rep->size;
    memcpy(new_rep->data, _rep->data, _rep->size + 1);
    _unref(_rep);
    _rep = new_rep;
}

void String::assign(const char* s, size_t n)
{
    if (n > _rep->cap || Atomic_get(&_rep->refs) != 1)
    {
        _unref(_rep);
        _rep = _new(n);
    }

    memcpy(_rep->data, s, n);
    _rep->data[n] = '\0';
    _rep->size = n;
}

void String::assign(const char* s)
{
    assign(s, strlen(s));
}

void String::append(const String& s)
{
    append(s._rep->data, s._rep->size);
}

void String::append(const char* s)
{
    append(s, strlen(s));
}

void String::append(const char* s, size_t n)
{
    size_t m = _rep->size + n;
    reserve(_next_pow_2(m));
    memcpy(_rep->data + _rep->size, s, n);
    _rep->size = m;
    _rep->data[m] = '\0';
}

void String::remove(size_t pos, size_t n)
{
    if (n == size_t(-1))
        n = _rep->size - pos;

    CIMPLE_ASSERT(pos + n <= _rep->size);

    if (Atomic_get(&_rep->refs) != 1)
	_reserve(_rep->cap);

    size_t rem = _rep->size - (pos + n);

    if (rem)
        memmove(_rep->data + pos , _rep->data + pos + n, rem);

    _rep->size -= n;
    _rep->data[_rep->size] = '\0';
}

String String::substr(size_t pos, size_t n)
{
    if (n == size_t(-1))
	n = _rep->size - pos;

    CIMPLE_ASSERT(pos + n <= _rep->size);
    return String(_rep->data + pos, n);
}

void String::clear()
{
    if (_rep->size)
    {
	if (Atomic_get(&_rep->refs) == 1)
	{
	    _rep->size = 0;
	    _rep->data[0] = '\0';
	}
	else
	{
	    _unref(_rep);
	    _rep = &_empty;
	}
    }
}

void String::set(size_t i, char c)
{
    CIMPLE_ASSERT(i <= _rep->size);

    if (Atomic_get(&_rep->refs) != 1)
	_reserve(_rep->cap);

    _rep->data[i] = c;
}

size_t String::find(char c) const
{
    char* p = strchr(_rep->data, c);
    return p ? (p - _rep->data) : size_t(-1);
}

CIMPLE_NAMESPACE_END

/* 
    To-do list:

	-  Implement insert()
	-  clone()
	-  substr()
	-  find()
	-  rfind()
	-  tolower()
	-  toupper()
	-  lexographical compare (for sorting).
	-  s/string/String/g?
*/
