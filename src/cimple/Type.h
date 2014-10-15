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

#ifndef _cimple_Type_h
#define _cimple_Type_h

#include "config.h"
#include "String.h"
#include "Datetime.h"

CIMPLE_NAMESPACE_BEGIN

/** CIM data types.
*/
enum Type
{
    BOOLEAN,
    UINT8,
    SINT8,
    UINT16,
    SINT16,
    UINT32,
    SINT32,
    UINT64,
    SINT64,
    REAL32,
    REAL64,
    CHAR16,
    STRING,
    DATETIME,
};

CIMPLE_LIBCIMPLE_LINKAGE 
extern size_t type_size[];

CIMPLE_LIBCIMPLE_LINKAGE 
extern const char* type_name[];

// Returns true if the index is one of the integer types defined above.
CIMPLE_LIBCIMPLE_LINKAGE 
extern char is_integer[];

// Returns true if the index is one of the "raw" types.
CIMPLE_LIBCIMPLE_LINKAGE 
extern char is_raw[];

CIMPLE_NAMESPACE_END

#endif /* _cimple_Type_h */
