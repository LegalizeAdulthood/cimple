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

static const uint32 INITIAL_STRING_SIZE = 32;

__String_Rep String::_empty;

inline void _ref(const __String_Rep* rep)
{
    if (rep != &String::_empty)
        Atomic_inc(&((__String_Rep*)rep)->refs);
}

inline void _unref(const __String_Rep* rep)
{
    if (rep != &String::_empty && 
        Atomic_dec_and_test(&((__String_Rep*)rep)->refs))
        ::operator delete((__String_Rep*)rep);
}

static uint32 _next_pow_2(uint32 x)
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

static inline __String_Rep* _new(size_t cap) 
{
    cap = _next_pow_2(cap);
    __String_Rep* rep = 
        (__String_Rep*)::operator new(sizeof(__String_Rep) + cap);

    rep->cap = cap;
    Atomic_create(&rep->refs, 1);
    return rep;
}

static inline void _reserve(__String_Rep*& _rep, size_t n)
{
    __String_Rep* new_rep = _new(n);
    new_rep->size = _rep->size;
    memcpy(new_rep->data, _rep->data, _rep->size + 1);
    _unref(_rep);
    _rep = new_rep;
}


static void _append_char(__String_Rep*& _rep, char c)
{
    __String_Rep* rep;

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

String::String(const String& s)
{
    _ref(_rep = s._rep);
}

String::~String()
{
    _unref(_rep);
}

void String::reserve(size_t n)
{
    if (n > _rep->cap || Atomic_get(&_rep->refs) != 1)
        _reserve(_rep, n);
}

void String::assign(const String& s)
{
    if (&s != this)
    {
        _unref(_rep);
        _ref(_rep = s._rep);
    }
}

void String::append(char c)
{
    if (_rep->size == _rep->cap || Atomic_get(&_rep->refs) != 1)
        _append_char(_rep, c);

    _rep->data[_rep->size++] = c;
    _rep->data[_rep->size] = '\0';
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
        _reserve(_rep, _rep->cap);

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
        _reserve(_rep, _rep->cap);

    _rep->data[i] = c;
}

size_t String::find(char c) const
{
    char* p = strchr(_rep->data, c);
    return p ? (p - _rep->data) : size_t(-1);
}

size_t String::find(char c, size_t n) const
{
    CIMPLE_ASSERT(n <= _rep->size);

    char* p = strchr((_rep->data + n), c);
    return p ? (p - _rep->data) : size_t(-1);
}

size_t String::find(const char* s) const
{
    char* p = strstr(_rep->data, s);
    return p ? (p - _rep->data) : size_t(-1);
}

size_t String::find(const String& s) const
{
    char* p = strstr(_rep->data, s._rep->data);
    return p ? (p - _rep->data) : size_t(-1);
}

bool String::equal(const String& s) const
{
    return _rep->size == s._rep->size &&
        memcmp(_rep->data, s._rep->data, _rep->size) == 0;
}

bool String::equal(const char* s) const
{
    return strcmp(_rep->data, s) == 0;
}

bool String::equal(const char* s, size_t n) const
{
    return _rep->size == n && memcmp(_rep->data, s, n) == 0;
}

bool String::equal(size_t pos, const char* s, size_t n) const
{
    return memcmp(_rep->data + pos, s, n) == 0;
}

bool String::equali(const String& s) const
{
    return _rep->size == s._rep->size &&
        strncasecmp(_rep->data, s._rep->data, _rep->size) == 0;
}

bool String::equali(const char* s) const
{
    return eqi(_rep->data, s);
}

bool String::equali(const char* s, size_t n) const
{
    return _rep->size == n && strncasecmp(s, _rep->data, n) == 0;
}

CIMPLE_NAMESPACE_END

