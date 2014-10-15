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

#ifndef _cimple_Meta_Value_h
#define _cimple_Meta_Value_h

#include "config.h"
#include "Type.h"

CIMPLE_NAMESPACE_BEGIN

struct Meta_Value
{
    int dummy;
};

template<class T>
struct Meta_Value_Scalar
{
    T value;
};

template<class T>
struct Meta_Value_Array
{
    const T* elements;
    size_t num_elements;
};

CIMPLE_CIMPLE_LINKAGE
void print(const Meta_Value* x, Type type, bool array);

CIMPLE_CIMPLE_LINKAGE
Meta_Value* clone(const Meta_Value* x, Type type, bool array);

CIMPLE_CIMPLE_LINKAGE
void destroy(Meta_Value* x, Type type, bool array);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Value_h */
