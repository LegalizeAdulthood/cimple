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

CIMPLE_CIMPLE_LINKAGE 
extern const uint8 __lower[256];

CIMPLE_CIMPLE_LINKAGE 
bool __eqi(const char* s1, const char* s2);

inline bool eqi(const char* s1, const char* s2)
{
    return 
        __lower[uint8(s1[0])] == __lower[uint8(s2[0])] && 
        strcasecmp(s1, s2) == 0;
}

CIMPLE_CIMPLE_LINKAGE
size_t strlcpy(char* dest, const char* src, size_t size);

CIMPLE_CIMPLE_LINKAGE
size_t strlcat(char* dest, const char* src, size_t size);

CIMPLE_CIMPLE_LINKAGE
int find_token(
    const char* str, 
    const char* delimiters, 
    const char*& start,
    const char*& end);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Strings_h */
