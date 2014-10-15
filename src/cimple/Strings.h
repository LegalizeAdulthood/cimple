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

#ifndef _cimple_Strings_h
#define _cimple_Strings_h

#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include "config.h"

CIMPLE_NAMESPACE_BEGIN

CIMPLE_LIBCIMPLE_LINKAGE 
bool str_to_uint16(const char* s, uint16& x);

CIMPLE_LIBCIMPLE_LINKAGE 
bool str_to_uint16(const char* s, size_t n, uint16& x);

CIMPLE_LIBCIMPLE_LINKAGE 
bool str_to_uint32(const char* s, uint32& x);

CIMPLE_LIBCIMPLE_LINKAGE 
bool str_to_uint32(const char* s, size_t n, uint32& x);

CIMPLE_LIBCIMPLE_LINKAGE 
bool str_to_size_t(const char* s, size_t n, size_t& x);

CIMPLE_LIBCIMPLE_LINKAGE 
char* str_clone(const char* s, size_t n);

CIMPLE_LIBCIMPLE_LINKAGE 
char* str_clone(const char* s);

CIMPLE_LIBCIMPLE_LINKAGE 
CIMPLE_PRINTF_ATTR(1, 2)
char* str_printf(const char* format, ...);

CIMPLE_LIBCIMPLE_LINKAGE 
char* str_vprintf(const char* format, va_list ap);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Strings_h */
