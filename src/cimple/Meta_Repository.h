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

#ifndef _cimple_Meta_Repository_h
#define _cimple_Meta_Repository_h

#include "config.h"
#include "Meta_Class.h"

CIMPLE_NAMESPACE_BEGIN

struct Meta_Repository
{
    const Meta_Class* const* meta_classes;
    size_t num_meta_classes;
};

CIMPLE_CIMPLE_LINKAGE
const Meta_Class* find_meta_class(
    const Meta_Repository* meta_repository,
    const char* class_name);

/* Returns 0 if #sub# is a subclass of #super# and 1 if not. Returns -1 if 
   unable to find either of the named classes in the meta repository or if 
   any of the pointers are null.
*/
CIMPLE_CIMPLE_LINKAGE
int is_subclass(
    const Meta_Repository* meta_repository,
    const char* super,
    const char* sub);

CIMPLE_NAMESPACE_END

#endif /* _cimple_Meta_Repository_h */
