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

#ifndef _cimple_integer_h
#define _cimple_integer_h

#include <cimple/config.h>
#include <cimple/linkage.h>
#include <cimple/Type.h>

CIMPLE_NAMESPACE_BEGIN

CIMPLE_CIMPLE_LINKAGE
int str_to_sint8(const char* str, sint8& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_sint16(const char* str, sint16& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_sint32(const char* str, sint32& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_sint64(const char* str, sint64& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_uint8(const char* str, uint8& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_uint16(const char* str, uint16& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_uint32(const char* str, uint32& x);

CIMPLE_CIMPLE_LINKAGE
int str_to_uint64(const char* str, uint64& x);

CIMPLE_CIMPLE_LINKAGE
const char* uint8_to_str(char buf[22], uint8 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* uint16_to_str(char buf[22], uint16 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* uint32_to_str(char buf[22], uint32 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* uint64_to_str(char buf[22], uint64 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* sint8_to_str(char buf[22], sint8 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* sint16_to_str(char buf[22], sint16 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* sint32_to_str(char buf[22], sint32 x, size_t& size);

CIMPLE_CIMPLE_LINKAGE
const char* sint64_to_str(char buf[22], sint64 x, size_t& size);

CIMPLE_NAMESPACE_END

#endif /* _cimple_integer_h */
