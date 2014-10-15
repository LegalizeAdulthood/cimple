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

#ifndef _cimple_String_h
#define _cimple_String_h

#include <cstring>
#include "config.h"
#include "Atomic.h"
#include "flags.h"
#include "Strings.h"

CIMPLE_NAMESPACE_BEGIN

struct __String_Rep
{
    Atomic refs;
    uint32 size;
    uint32 cap;
    char data[1];
    __String_Rep() { Atomic_create(&refs, 2); }
};

class CIMPLE_CIMPLE_LINKAGE String
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

    size_t find(char c) const;


private:
    __String_Rep* _rep;
    static __String_Rep _empty;
    friend void _ref(const __String_Rep* rep);
    friend void _unref(const __String_Rep* rep);
};

inline String::String() : _rep(&_empty)
{
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

inline bool eqi(const String& s1, const String& s2)
{
    return eqi(s1.c_str(), s2.c_str());
}

inline bool eqi(const String& s1, const char* s2)
{
    return eqi(s1.c_str(), s2);
}

inline bool eqi(const char* s1, const String& s2)
{
    return eqi(s1, s2.c_str());
}

inline void __clear(String& x) 
{ 
    x.clear(); 
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_String_h */
