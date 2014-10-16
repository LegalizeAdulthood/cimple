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

#ifndef _pegadapter_Str_h
#define _pegadapter_Str_h

#include <cimple/config.h>
#include <Pegasus/Common/String.h>
#include <Pegasus/Common/CIMName.h>
#include <Pegasus/Common/Exception.h>
#include <Pegasus/Common/CIMDateTime.h>

CIMPLE_NAMESPACE_BEGIN

class Str
{
public:

    Str(const P_String& s) : _cstr(s.getCString())
    {
    }

    Str(const P_CIMName& n) : _cstr(n.getString().getCString())
    {
    }

    Str(const P_CIMNamespaceName& n) : _cstr(n.getString().getCString())
    {
    }

    Str(const P_Exception& e) : _cstr(e.getMessage().getCString())
    {
    }

    Str(const P_CIMDateTime& x) : _cstr(x.toString().getCString())
    {
    }

    ~Str()
    {
    }

    const char* operator*() const { return (const char*)_cstr; }

    operator const char*() const { return (const char*)_cstr; }

private:
    P_CString _cstr;
};

CIMPLE_NAMESPACE_END

#endif /* _pegadapter_Str_h */
