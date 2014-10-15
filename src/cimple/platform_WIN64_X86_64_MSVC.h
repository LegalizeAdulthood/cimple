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

#ifndef _cimple_WIN64_X86_64_MSVC_h
#define _cimple_WIN64_X86_64_MSVC_h

#include <cstdarg>

#pragma warning ( disable : 4996 )

#pragma warning ( disable : 4251 )

// identifier was truncated to '255' characters in the debug information.
#pragma warning ( disable : 4786 )

// forcing value to bool 'true' or 'false'
#pragma warning ( disable : 4800 )

// conversion from <type1> to <type2>: possible loss of data.
#pragma warning ( disable : 4244 )

// 'sprintf' name was marked as #pragma deprecated
#pragma warning ( disable : 4995 )

// DEPRECATE CIMPLE_WINDOWS define in favor of CIMPLE_WINDOWS_MSVC
// to allow possible other compilers in future
#define CIMPLE_WINDOWS

#define CIMPLE_WINDOWS_MSVC
#define CIMPLE_UINT64 unsigned __int64
#define CIMPLE_SINT64 signed __int64
#define CIMPLE_HIDE
#define CIMPLE_WINDOWS
#define CIMPLE_WINDOWS_64
#define CIMPLE_LLU "%I64u"
#define CIMPLE_LLD "%I64d"
#define CIMPLE_IMPORT __declspec(dllimport)
#define CIMPLE_EXPORT __declspec(dllexport)
#define for if (0) ; else for

inline int strcasecmp(const char* s1, const char* s2)
{
    return _stricmp(s1, s2);
}

inline int strncasecmp(const char* s1, const char* s2, size_t n)
{
    return _strnicmp(s1, s2, n);
}

inline int vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
    return _vsnprintf(str, size, format, ap);
}

typedef __int32 ssize_t;

#define CIMPLE_BIG_ENDIAN

#define CIMPLE_PLATFORM_ID "WIN64_X86_64_MSVC"

#define CIMPLE_UINT64_LITERAL(X) ((uint64)(X))
#define CIMPLE_SINT64_LITERAL(X) ((sint64)(X))

#endif /* _cimple_WIN64_X86_64_MSVC_h */
