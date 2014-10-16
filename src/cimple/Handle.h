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

#ifndef _cimple_Handle_h
#define _cimple_Handle_h

#include "config.h"
#include "Instance.h"
#include "Exception.h"

CIMPLE_NAMESPACE_BEGIN

/** Class Handle.
*/
class CIMPLE_CIMPLE_LINKAGE Handle
{
public:

    Handle(const Handle& x);

    explicit Handle(Instance* inst);

    ~Handle();

    Handle& operator=(const Handle& x);

    const Instance* instance() const { return _inst; }

    void print() const;

protected:

    Handle();

    void _cow();

    Instance* _inst;

    static void _construct(
        Handle& to_handle,
        const Meta_Class& to_mc,
        const Handle& from_handle);
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Handle_h */
