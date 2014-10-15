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

#ifndef _cimple_char16_h
#define _cimple_char16_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN

class char16
{
public:
    char16();
    char16(const char16& x);
    char16(uint16 x);
    char16& operator=(const char16& x);
    char16& operator=(uint16 x);
    uint16 code() const;
    void code(uint16 code);
private:
    uint16 _code;
};

inline char16::char16() : _code(0)
{
}

inline char16::char16(const char16& x) : _code(x._code) 
{ 
}

inline char16::char16(uint16 x) : _code(x) 
{ 
}

inline char16& char16::operator=(const char16& x) 
{ 
    _code = x._code; 
    return *this; 
}

inline char16& char16::operator=(uint16 x) 
{ 
    _code = x; 
    return *this; 
}

inline uint16 char16::code() const 
{ 
    return _code; 
}

inline void char16::code(uint16 code) 
{ 
    _code = code; 
}

inline bool operator==(const char16& x, const char16& y)
{
    return x.code() == y.code();
}

inline bool operator!=(const char16& x, const char16& y)
{
    return !operator==(x, y);
}

inline bool operator<(const char16& x, const char16& y)
{
    return x.code() < y.code();
}

inline bool operator<=(const char16& x, const char16& y)
{
    return x.code() <= y.code();
}

inline bool operator>(const char16& x, const char16& y)
{
    return x.code() > y.code();
}

inline bool operator>=(const char16& x, const char16& y)
{
    return x.code() >= y.code();
}

inline void __clear(char16& x)
{
    x = 0;
}

CIMPLE_NAMESPACE_END

#endif /* _cimple_char16_h */
