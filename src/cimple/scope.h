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

#ifndef _cimple_scope_h
#define _cimple_scope_h

#include "config.h"

CIMPLE_NAMESPACE_BEGIN

#define CIMPLE_SCOPE_SCHEMA             CIMPLE_BIT(0)
#define CIMPLE_SCOPE_CLASS              CIMPLE_BIT(1)
#define CIMPLE_SCOPE_ASSOCIATION        CIMPLE_BIT(2)
#define CIMPLE_SCOPE_INDICATION         CIMPLE_BIT(3)
#define CIMPLE_SCOPE_PROPERTY           CIMPLE_BIT(4)
#define CIMPLE_SCOPE_REFERENCE          CIMPLE_BIT(5)
#define CIMPLE_SCOPE_METHOD             CIMPLE_BIT(6)
#define CIMPLE_SCOPE_PARAMETER          CIMPLE_BIT(7)
#define CIMPLE_SCOPE_ANY                (1|2|4|8|16|32|64|128)

CIMPLE_NAMESPACE_END

#endif /* _cimple_scope_h */
