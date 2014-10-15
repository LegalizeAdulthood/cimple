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

#ifndef _cimple_flags_h
#define _cimple_flags_h

#include "config.h"

//------------------------------------------------------------------------------
//
// These are used to build a mask for the flags property for any of the meta
// objects (e.g., Meta_Class, Meta_Property, ...).
//
//------------------------------------------------------------------------------

#define CIMPLE_FLAG_PROPERTY 		CIMPLE_BIT(0)
#define CIMPLE_FLAG_REFERENCE 		CIMPLE_BIT(1)
#define CIMPLE_FLAG_METHOD 		CIMPLE_BIT(2)
#define CIMPLE_FLAG_CLASS 		CIMPLE_BIT(4)
#define CIMPLE_FLAG_ASSOCIATION 	CIMPLE_BIT(5)
#define CIMPLE_FLAG_INDICATION 		CIMPLE_BIT(6)
#define CIMPLE_FLAG_KEY			CIMPLE_BIT(7)
#define CIMPLE_FLAG_IN 			CIMPLE_BIT(8)
#define CIMPLE_FLAG_OUT 		CIMPLE_BIT(9)
#define CIMPLE_FLAG_LOCAL		CIMPLE_BIT(10)
#define CIMPLE_FLAG_EMBEDDED_OBJECT	CIMPLE_BIT(11)
#define CIMPLE_FLAG_STATIC		CIMPLE_BIT(12)

#define CIMPLE_FLAG_ANY_FEATURE \
	(CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_METHOD|CIMPLE_FLAG_REFERENCE)

#endif /* _cimple_flags_h */
