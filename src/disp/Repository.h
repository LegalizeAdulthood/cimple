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

#ifndef _cimple_Repository_h
#define _cimple_Repository_h

#include <dlfcn.h>
#include <cimple/config.h>
#include <cimple/Meta_Class.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLEDISP_LINKAGE Repository
{
public:

    Repository(void* handle, Repository_Proc proc);

    ~Repository();

    const Meta_Class* const* meta_classes() { return _meta_classes; }

    const size_t num_meta_classes() { return _num_meta_classes; }

private:

    void* _handle;
    const Meta_Class* const* _meta_classes;
    size_t _num_meta_classes;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Repository_h */
