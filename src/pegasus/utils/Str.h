/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009
**               Michael Brasher, Karl Schopmeyer
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

#ifndef _cimple_pegasus_utils_Str_h
#define _cimple_pegasus_utils_Str_h

#include <cimple/config.h>
#include "pegasus.h"

CIMPLE_NAMESPACE_BEGIN

/*
    Create the Pegasus CString for a variety of Pegasus
    Objects including String, CIMName, CIMNamespaceName,
    Exception, CIMDateTime, and CIMObjectPath.
*/
class Str
{
public:

    Str(const Pegasus::String& s) : _cstr(s.getCString())
    {
    }

    Str(const Pegasus::CIMName& n) : _cstr(n.getString().getCString())
    {
    }

    Str(const Pegasus::CIMNamespaceName& n) : _cstr(n.getString().getCString())
    {
    }

    Str(const Pegasus::Exception& e) : _cstr(e.getMessage().getCString())
    {
    }

    Str(const Pegasus::CIMDateTime& x) : _cstr(x.toString().getCString())
    {
    }

    Str(const Pegasus::CIMObjectPath& x) : _cstr(x.toString().getCString())
    {
    }

    ~Str()
    {
    }

    const char* operator*() const { return (const char*)_cstr; }

    operator const char*() const { return (const char*)_cstr; }

private:
    Pegasus::CString _cstr;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_pegasus_utils_Str_h */
