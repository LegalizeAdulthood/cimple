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

#ifndef _MOF_Config_h
#define _MOF_Config_h

#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>

#ifdef CIMPLE_WINDOWS
# define MOF_WINDOWS
#endif

#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <cstdlib>
#include <cstring>

#define MOF_HAVE_STRCASECMP
#define MOF_ASSERT(COND) assert(COND)

#ifdef MOF_WINDOWS
#  define strcasecmp stricmp
#  define MOF_PRINTF_ATTR(A1, A2) /* empty */
   typedef unsigned __int64 MOF_uint64;
   typedef signed __int64 MOF_sint64;
#else
#  define MOF_PRINTF_ATTR(A1, A2) __attribute__ ((format (printf, A1, A2)))
   typedef unsigned long long MOF_uint64;
   typedef long long MOF_sint64;
#endif

#define MOF_LINKAGE /* */

#define MOF_PATH_SIZE 512

typedef unsigned char MOF_uint8;
typedef signed char MOF_sint8;
typedef unsigned short MOF_uint16;
typedef signed short MOF_sint16;
typedef unsigned int MOF_uint32;
typedef signed int MOF_sint32;
typedef char* MOF_String;
typedef float MOF_real32;
typedef double MOF_real64;
typedef unsigned short MOF_char16; /* UCS-2 character */

typedef unsigned int MOF_mask;

#ifdef MOF_WINDOWS
inline MOF_sint64 strtoll(const char* str, char** end_ptr, int base)
{
    return strtol(str, end_ptr, base);
}
# pragma warning ( disable : 4996 )
#endif


#endif /* _MOF_Config_h */
