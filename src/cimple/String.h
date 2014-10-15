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

#ifndef _cimple_String_h
#define _cimple_String_h

#include <cstring>
#include "config.h"
#include "Type.h"
#include "Atomic.h"
#include "flags.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LIBCIMPLE_LINKAGE String
{
public:

    String();

    String(const String& s);

    String(const char* s);

    String(const char* s1, const char* s2);

    String(const char* s1, const char* s2, const char* s3);

    String(const char* s, size_t n);

    ~String();

    void reserve(size_t n);

    void assign(const String& s);

    void assign(const char* s, size_t n);

    void assign(const char* s);

    void append(const String& s);

    void append(const char* s);

    void append(const char* s, size_t n);

    void append(char c);

    void remove(size_t pos, size_t n);

    String substr(size_t pos, size_t n = size_t(-1));

    String& operator=(const String& s);

    String& operator=(const char* s);

    void clear();

    const char* c_str() const;

    size_t size() const;

    bool empty() const;

    size_t capacity() const;

    char operator[](size_t i) const;

    void set(size_t i, char c);

    bool equal(const String& s) const;

    bool equal(const char* s) const;

    bool equal(const char* s, size_t n) const;

    bool equal(size_t pos, const char* s, size_t n) const;

    bool equali(const String& s) const;

    bool equali(const char* s) const;

    bool equali(const char* s, size_t n) const;

    /** Returns true if the given string is a prefix of this string.
    */
    bool is_prefix(const char* s, size_t n) const;

    /** Returns true if the given string is a suffix of this string.
    */
    bool is_suffix(const char* s, size_t n) const;

private:

    struct Rep
    {
	uint32 size;
	uint32 cap;
	Atomic refs;
	char data[1];
	Rep() { Atomic_create(&refs, 2); }
    };

    static CIMPLE_HIDE Rep* _new(size_t cap);

    static void _ref(const Rep* rep);

    static void _unref(const Rep* rep);

    void _append_char(char c);

    void _reserve(size_t n);

    static Rep _empty;
    Rep* _rep;
};

inline void String::_ref(const String::Rep* rep)
{
    if (rep != &String::_empty)
	Atomic_inc(&((Rep*)rep)->refs);
}

inline void String::_unref(const String::Rep* rep)
{
    if (rep != &String::_empty && Atomic_dec_and_test(&((Rep*)rep)->refs))
	::operator delete((Rep*)rep);
}

inline String::String() : _rep(&_empty)
{
}

inline String::String(const String& s)
{
    _ref(_rep = s._rep);
}

inline String::~String()
{
    _unref(_rep);
}

inline void String::reserve(size_t n)
{
    if (n > _rep->cap || Atomic_get(&_rep->refs) != 1)
	_reserve(n);
}

inline void String::assign(const String& s)
{
    if (&s != this)
    {
	_unref(_rep);
	_ref(_rep = s._rep);
    }
}

inline void String::append(char c)
{
    if (_rep->size == _rep->cap || Atomic_get(&_rep->refs) != 1)
	_append_char(c);

    _rep->data[_rep->size++] = c;
    _rep->data[_rep->size] = '\0';
}

inline String& String::operator=(const String& s)
{
    assign(s);
    return *this;
}

inline String& String::operator=(const char* s)
{
    assign(s);
    return *this;
}

inline const char* String::c_str() const
{
    return _rep->data;
}

inline size_t String::size() const
{
    return _rep->size;
}

inline bool String::empty() const
{
    return _rep->size == 0;
}

inline size_t String::capacity() const
{
    return _rep->cap;
}

inline char String::operator[](size_t i) const
{
    CIMPLE_ASSERT(i <= _rep->size);
    return _rep->data[i];
}

inline bool String::equal(const String& s) const
{
    return _rep->size == s._rep->size &&
	memcmp(_rep->data, s._rep->data, _rep->size) == 0;
}

inline bool String::equal(const char* s) const
{
    return strcmp(_rep->data, s) == 0;
}

inline bool String::equal(const char* s, size_t n) const
{
    return _rep->size == n && memcmp(_rep->data, s, n) == 0;
}

inline bool String::equal(size_t pos, const char* s, size_t n) const
{
    return memcmp(_rep->data + pos, s, n) == 0;
}

inline bool String::equali(const String& s) const
{
    return _rep->size == s._rep->size &&
	strncasecmp(_rep->data, s._rep->data, _rep->size) == 0;
}

inline bool String::equali(const char* s) const
{
    return strcasecmp(_rep->data, s) == 0;
}

inline bool String::equali(const char* s, size_t n) const
{
    return _rep->size == n && strncasecmp(s, _rep->data, n) == 0;
}

inline bool String::is_prefix(const char* s, size_t n) const
{
    return _rep->size >= n && memcmp(_rep->data, s, n) == 0;
}

inline bool String::is_suffix(const char* s, size_t n) const
{
    return _rep->size >= n && memcmp(_rep->data + _rep->size - n, s, n) == 0;
}

inline bool operator==(const String& s1, const String& s2)
{
    return s1.equal(s2);
}

inline bool operator==(const String& s1, const char* s2)
{
    return s1.equal(s2);
}

inline bool operator==(const char* s1, const String& s2)
{
    return s2.equal(s1);
}

inline bool operator!=(const String& s1, const String& s2)
{
    return !operator==(s1, s2);
}

inline bool operator!=(const String& s1, const char* s2)
{
    return !operator==(s1, s2);
}

inline bool operator!=(const char* s1, const String& s2)
{
    return !operator==(s1, s2);
}

inline void clear(String& x) 
{ 
    x.clear(); 
}

/* Returns the initial segment  of s which consists entirely of characters 
   in accept.
*/
inline String spn(const String& s, const char* accept)
{
    return String(s.c_str(), strspn(s.c_str(), accept));
}

/* Returns the initial segment  of s which consists entirely of characters 
   not in reject.
*/
inline String cspn(const String& s, const char* reject)
{
    return String(s.c_str(), strcspn(s.c_str(), reject));
}

/* Returns the concatenation of s1 and s2. 
*/
inline String cat(const String& s1, const String& s2)
{
    String s = s1;
    s.append(s2);
    return s;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_String_h */
