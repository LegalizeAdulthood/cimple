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


#ifndef _WMI_SafeArr_h
#define _WMI_SafeArr_h

#include <cimple/cimple.h>
#include <wbemprov.h>
#include "log.h"

CIMPLE_NAMESPACE_BEGIN

class SafeArr
{
public:

    SafeArr(VARTYPE type, long size)
    {
        SAFEARRAYBOUND sab;
        sab.lLbound = 0; 
        sab.cElements = size;
        _rep = SafeArrayCreate(type, 1, &sab);
    }

    SafeArr(SAFEARRAY* rep) : _rep(rep)
    {
    }

    ~SafeArr()
    {
        if (_rep)
            SafeArrayDestroy(_rep);
    }

    SAFEARRAY* steal()
    {
        SAFEARRAY* result = _rep;
        _rep = 0;
        return result;
    }

    bool size(long& x)
    {
        long tmp;

        if (SafeArrayGetUBound(_rep, 1, &tmp) != S_OK)
            return false;

        x = tmp + 1;
        return true;
    }

    bool put(long index, void* data)
    {
        return SafeArrayPutElement(_rep, &index, data) == S_OK;
    }

    bool get(long index, void* data)
    {
        return SafeArrayGetElement(_rep, &index, data) == S_OK;
    }

private:
    SAFEARRAY* _rep;

    SafeArr();
};

CIMPLE_NAMESPACE_END

#endif /* _WMI_SafeArr_h */
