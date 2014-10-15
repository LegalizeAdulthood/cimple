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

#ifndef _cimple_flags_h
#define _cimple_flags_h

#include "config.h"

//------------------------------------------------------------------------------
//
// These are used to build a mask for the flags property for any of the meta
// objects (e.g., Meta_Class, Meta_Property, ...).
//
//------------------------------------------------------------------------------

// Meta object type tags:

#define CIMPLE_FLAG_PROPERTY CIMPLE_BIT(0)
#define CIMPLE_FLAG_REFERENCE CIMPLE_BIT(1)
#define CIMPLE_FLAG_METHOD CIMPLE_BIT(2)
#define CIMPLE_FLAG_CLASS CIMPLE_BIT(3)
#define CIMPLE_FLAG_ABSTRACT CIMPLE_BIT(4)
#define CIMPLE_FLAG_AGGREGATE CIMPLE_BIT(5)
#define CIMPLE_FLAG_AGGREGATION CIMPLE_BIT(6)
#define CIMPLE_FLAG_ASSOCIATION CIMPLE_BIT(7)
#define CIMPLE_FLAG_COMPOSITION CIMPLE_BIT(8)
#define CIMPLE_FLAG_COUNTER CIMPLE_BIT(9)
#define CIMPLE_FLAG_DELETE CIMPLE_BIT(10)
#define CIMPLE_FLAG_DN CIMPLE_BIT(11)
#define CIMPLE_FLAG_EMBEDDED_OBJECT CIMPLE_BIT(12)
#define CIMPLE_FLAG_EXCEPTION CIMPLE_BIT(13)
#define CIMPLE_FLAG_EXPENSIVE CIMPLE_BIT(14)
#define CIMPLE_FLAG_EXPERIMENTAL CIMPLE_BIT(15)
#define CIMPLE_FLAG_GAUGE CIMPLE_BIT(16)
#define CIMPLE_FLAG_IF_DELETED CIMPLE_BIT(17)
#define CIMPLE_FLAG_IN CIMPLE_BIT(18)
#define CIMPLE_FLAG_INDICATION CIMPLE_BIT(19)
#define CIMPLE_FLAG_INVISIBLE CIMPLE_BIT(20)
#define CIMPLE_FLAG_KEY CIMPLE_BIT(21)
#define CIMPLE_FLAG_LARGE CIMPLE_BIT(22)
#define CIMPLE_FLAG_OCTET_STRING CIMPLE_BIT(23)
#define CIMPLE_FLAG_OUT CIMPLE_BIT(24)
#define CIMPLE_FLAG_READ CIMPLE_BIT(25)
#define CIMPLE_FLAG_REQUIRED CIMPLE_BIT(26)
#define CIMPLE_FLAG_STATIC CIMPLE_BIT(27)
#define CIMPLE_FLAG_TERMINAL CIMPLE_BIT(28)
#define CIMPLE_FLAG_WEAK CIMPLE_BIT(29)
#define CIMPLE_FLAG_WRITE CIMPLE_BIT(30)
#define CIMPLE_FLAG_EMBEDDED_INSTANCE CIMPLE_BIT(31)

#define CIMPLE_FLAG_ANY_FEATURE \
    (CIMPLE_FLAG_PROPERTY| \
    CIMPLE_FLAG_METHOD| \
    CIMPLE_FLAG_REFERENCE)

#define CIMPLE_FLAG_ANY_QUALIFIER \
    (CIMPLE_FLAG_ABSTRACT| \
    CIMPLE_FLAG_AGGREGATE| \
    CIMPLE_FLAG_AGGREGATION| \
    CIMPLE_FLAG_ASSOCIATION| \
    CIMPLE_FLAG_COMPOSITION| \
    CIMPLE_FLAG_COUNTER| \
    CIMPLE_FLAG_DELETE| \
    CIMPLE_FLAG_DN| \
    CIMPLE_FLAG_EMBEDDED_OBJECT| \
    CIMPLE_FLAG_EXCEPTION| \
    CIMPLE_FLAG_EXPENSIVE| \
    CIMPLE_FLAG_EXPERIMENTAL| \
    CIMPLE_FLAG_GAUGE| \
    CIMPLE_FLAG_IF_DELETED| \
    CIMPLE_FLAG_IN| \
    CIMPLE_FLAG_INDICATION| \
    CIMPLE_FLAG_INVISIBLE| \
    CIMPLE_FLAG_KEY| \
    CIMPLE_FLAG_LARGE| \
    CIMPLE_FLAG_OCTET_STRING| \
    CIMPLE_FLAG_OUT| \
    CIMPLE_FLAG_READ| \
    CIMPLE_FLAG_REQUIRED| \
    CIMPLE_FLAG_STATIC| \
    CIMPLE_FLAG_TERMINAL| \
    CIMPLE_FLAG_WEAK| \
    CIMPLE_FLAG_WRITE)

CIMPLE_NAMESPACE_BEGIN

CIMPLE_CIMPLE_LINKAGE
extern const char* flag_names[];

CIMPLE_CIMPLE_LINKAGE
extern const size_t num_flag_names;

CIMPLE_CIMPLE_LINKAGE
extern size_t flag_name_to_index(const char* flag_name);

CIMPLE_NAMESPACE_END

#endif /* _cimple_flags_h */
