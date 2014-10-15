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

#ifndef _cimple_config_h
#define _cimple_config_h

#include <platform.h>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <new>
#include "options.h"

//------------------------------------------------------------------------------
//
// Include the selected platform header file:
//
//------------------------------------------------------------------------------

#if defined(CIMPLE_PLATFORM_LINUX_IX86_GNU)
# include "platform_LINUX_IX86_GNU.h"
#elif defined(CIMPLE_PLATFORM_LINUX_X86_64_GNU)
# include "platform_LINUX_X86_64_GNU.h"
#elif defined(CIMPLE_PLATFORM_LINUX_PPC_GNU)
# include "platform_LINUX_PPC_GNU.h"
#elif defined(CIMPLE_PLATFORM_WIN32_IX86_MSVC)
# include "platform_WIN32_IX86_MSVC.h"
#else
# error "Invalid system. System is misconfigured"
#endif

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

#define CIMPLE_ENTRY_POINT extern "C"

#define CIMPLE_NAMESPACE_BEGIN namespace cimple {
#define CIMPLE_NAMESPACE_END }

#define CIMPLE_WARNING(X) \
    fprintf(stderr, "CIMPLE_WARNING: %s(%d): %s\n", __FILE__, __LINE__, #X)

#define CIMPLE_UINT8_MIN 0
#define CIMPLE_UINT8_MAX 255

#define CIMPLE_SINT8_MIN (-CIMPLE_SINT8_MAX-1)
#define CIMPLE_SINT8_MAX 127

#define CIMPLE_UINT16_MIN 0
#define CIMPLE_UINT16_MAX 65535

#define CIMPLE_SINT16_MIN (-CIMPLE_SINT16_MAX-1)
#define CIMPLE_SINT16_MAX 32767

#define CIMPLE_UINT32_MIN 0
#define CIMPLE_UINT32_MAX 4294967295U

#define CIMPLE_SINT32_MIN (-CIMPLE_SINT32_MAX-1)
#define CIMPLE_SINT32_MAX 2147483647

#define CIMPLE_UINT64_MIN 0
#define CIMPLE_UINT64_MAX (uint64(-1)) /* 18446744073709551615 */

#define CIMPLE_SINT64_MIN (-CIMPLE_SINT64_MAX-1)
#define CIMPLE_SINT64_MAX 9223372036854775807LL

#ifdef __USE_GNU
# define CIMPLE_TRACE cimple::__cimple_trace(__FILE__, __LINE__, __FUNCTION__)
#else
# define CIMPLE_TRACE cimple::__cimple_trace(__FILE__, __LINE__, "unknown")
#endif

#ifdef CIMPLE_DEBUG
# define CIMPLE_ASSERT(COND) \
    do \
    { \
	if (!(COND)) \
	    __cimple_assert(__FILE__, __LINE__, __FUNCTION__, #COND); \
    } \
    while (0)
#else
# define CIMPLE_ASSERT(COND) /* */
#endif

#ifdef __USE_GNU
# define CIMPLE_PRINTF_ATTR(A1, A2) __attribute__((format (printf, A1, A2)))
#else
# define CIMPLE_PRINTF_ATTR(A1, A2) /* empty */
#endif

#define CIMPLE_OFF(CLASS, FIELD) (((size_t)(void*)&(((CLASS*)8)->FIELD))-8)

#define CIMPLE_ARRAY_SIZE(X) (sizeof(X) / sizeof X[0])

#define CIMPLE_BIT(N) (1 << (N))

#define __CIMPLE_PASTE(X,Y) X##Y

#define CIMPLE_PASTE(X,Y) __CIMPLE_PASTE(X,Y)

#define CIMPLE_FL __FILE__, __LINE__

#define CIMPLE_RESTART(EXPR, RC) \
    while (((RC = (EXPR)) == -1) && (errno == EINTR))

#define CIMPLE_RETURN(X) \
    do \
    { \
        printf("CIMPLE_RETURN: %s(%d): %s\n", __FILE__,__LINE__,__FUNCTION__); \
        return X; \
    } \
    while (0)

#ifdef CIMPLE_BUILDING_LIBCIMPLE
# define CIMPLE_LIBCIMPLE_LINKAGE CIMPLE_EXPORT
#else
# ifdef CIMPLE_LINK_STATIC_LIBCIMPLE
#   define CIMPLE_LIBCIMPLE_LINKAGE /* empty */
#else
#   define CIMPLE_LIBCIMPLE_LINKAGE CIMPLE_IMPORT
# endif
#endif

// These definitions are for generated classes to use:
#ifdef CIMPLE_INTERNAL
# define CIMPLE_LINKAGE CIMPLE_EXPORT
#else
# ifdef CIMPLE_LINK_STATIC_CIMPLE
#  define CIMPLE_LINKAGE /* empty */
# else
#  define CIMPLE_LINKAGE CIMPLE_IMPORT
#endif
#endif

// CIMPLE_BIG_ENDIAN indicates that the endian type of the platform runs
// converse to the one used on the wire. The platform that defines this
// flag will have to do more work when packing and unpacking data from
// the network. You can undefine this to make your platform run faster.
#ifdef CIMPLE_BIG_ENDIAN
# define CIMPLE_CONVERSE_ENDIAN
#endif

CIMPLE_NAMESPACE_BEGIN

CIMPLE_EXPORT void __cimple_trace(
    const char* file, 
    size_t line,
    const char* function);

CIMPLE_EXPORT void __cimple_assert(
    const char* file, 
    size_t line,
    const char* function, 
    const char* cond);

typedef bool boolean;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef CIMPLE_UINT64 uint64;
typedef CIMPLE_SINT64 sint64;
typedef float real32;
typedef double real64;

struct char16
{
    uint16 code;

    char16() { }
    char16(const char16& x) : code(x.code) { }
    char16(uint16 x) : code(x) { }
    char16& operator=(const char16& x) { code = x.code; return *this; }
    char16& operator=(uint16 x) { code = x; return *this; }
    operator uint16() const { return code; }
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_config_h */
