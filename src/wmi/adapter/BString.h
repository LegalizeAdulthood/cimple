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

#ifndef _BString_h
#define _BString_h

#include <cimple/cimple.h>
#include <objbase.h>
#include <wbemprov.h>
#include "utils.h"

CIMPLE_NAMESPACE_BEGIN

enum WSTR_Tag { WSTR_TAG };

enum BSTR_Tag { BSTR_TAG };

class BString
{
public:

    BString() : _rep(0)
    {
    }

    BString(const char* cstr)
    {
        _rep = cstr2bstr(cstr);
    }

    BString(const String& str)
    {
        _rep = str2bstr(str);
    }

    BString(const LPWSTR wstr, WSTR_Tag)
    {
        _rep = SysAllocString(wstr);
    }

    BString(BSTR bstr, BSTR_Tag) : _rep(bstr) 
    {
    }

    ~BString()
    {
        clear();
    }

    BSTR rep() 
    { 
        return _rep; 
    }

    void clear()
    {
        if (_rep)
        {
            SysFreeString(_rep);
            _rep = 0;
        }
    }

    void set(const char* cstr)
    {
        clear();
        _rep = cstr2bstr(cstr);
    }

    void set(const String& str)
    {
        clear();
        _rep = str2bstr(str);
    }

    void set(const LPWSTR wstr, WSTR_Tag)
    {
        clear();
        _rep = SysAllocString(wstr);
    }

    void set(BSTR bstr, BSTR_Tag)
    {
        clear();
        _rep = bstr;
    }

private:

    BString(const BString&);
    BString& operator=(const BString&);

    BSTR _rep;
};

CIMPLE_NAMESPACE_END

#endif /* _BString_h */
