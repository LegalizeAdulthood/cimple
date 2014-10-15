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

#ifndef _converter_CStr_h
#define _converter_CStr_h

#include <cimple/cimple.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/String.h>
#include <Pegasus/Common/CIMName.h>

CIMPLE_NAMESPACE_BEGIN

/** An internal class to make it easier to convert Pegasus strings to
    C strings. For example, the following is safe:

        Pegasus::String tmp;
        printf("tmp: %s\n", CStr(tmp).c_str());

    A constructor is also provided for Pegasus::CIMName.
*/
class CStr
{
public:

    CStr(const Pegasus::String& str);

    CStr(const Pegasus::CIMName& name);

    const char* c_str() { return _cstr; }

    operator const char*() { return _cstr; }

public:

    Pegasus::CString _cstr;
};

inline CStr::CStr(const Pegasus::String& str) : _cstr(str.getCString())
{
}

inline CStr::CStr(const Pegasus::CIMName& name) 
    : _cstr(name.getString().getCString())
{
}

CIMPLE_NAMESPACE_END

#endif /* _converter_CStr_h */
