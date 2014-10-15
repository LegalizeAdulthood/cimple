
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

#include <cctype>
#include <cstdio>
#include <cstdarg>
#include <cctype>
#include "Strings.h"

CIMPLE_NAMESPACE_BEGIN

// ATTN: can we get rid of these functions?

template<class T>
struct Str_To_Int
{
    static bool func(const char* s, size_t n, T& x)
    {
	// ATTN: check for overflow!

	x = 0;
	T r = 1;

	for (const char* p = &s[n]; n--; )
	{
	    char c = *--p;

	    if (!isdigit(c))
		return false;

	    x += r * (c - '0');
	    r *= 10;
	}

	return true;
    }
};

bool str_to_uint16(const char* s, size_t n, uint16& x)
{
    return Str_To_Int<uint16>::func(s, n, x);
}

bool str_to_uint32(const char* s, size_t n, uint32& x)
{
    return Str_To_Int<uint32>::func(s, n, x);
}

bool str_to_uint64(const char* s, size_t n, uint64& x)
{
    return Str_To_Int<uint64>::func(s, n, x);
}

bool str_to_size_t(const char* s, size_t n, size_t& x)
{
    return Str_To_Int<size_t>::func(s, n, x);
}

bool str_to_uint16(const char* s, uint16& x)
{
    char* end;
    x = strtol(s, &end, 10);
    return *end == '\0';
}

bool str_to_uint32(const char* s, uint32& x)
{
    char* end;
    x = strtol(s, &end, 10);
    return *end == '\0';
}

char* str_clone(const char* s, size_t n)
{
    char* p = new char[n+1];
    memcpy(p, s, n);
    p[n] = '\0';
    return p;
}

char* str_clone(const char* s) 
{
    return str_clone(s, strlen(s)); 
}

char* str_printf(const char* format, ...)
{
    va_list ap;
    char* str;

    va_start(ap, format);
    vasprintf(&str, format, ap);
    va_end(ap);

    return str;
}

char* str_vprintf(const char* format, va_list ap)
{
    char* str;
    vasprintf(&str, format, ap);
    return str;
}

CIMPLE_NAMESPACE_END
