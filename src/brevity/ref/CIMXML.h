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

#ifndef _brevity_CIMXML_h
#define _brevity_CIMXML_h

#include <cimple/cimple.h>
#include "linkage.h"
#include "defines.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_BREVITY_LINKAGE CIMXML
{
public:

    static void xml_line(Buffer& out)
    {
        out.append(STRLIT("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"));
    }

    static void start_CIM(Buffer& out)
    {
        out.append(STRLIT("<CIM CIMVERSION=\"2.0\" DTDVERSION=\"2.0\">\n"));
    }

    static void end_CIM(Buffer& out)
    {
        out.append(STRLIT("</CIM>\n"));
    }

    static void start_MESSAGE(Buffer& out, uint64 id);

    static void end_MESSAGE(Buffer& out)
    {
        out.append(STRLIT("</MESSAGE>\n"));
    }

    static void start_SIMPLEREQ(Buffer& out)
    {
        out.append(STRLIT("<SIMPLEREQ>\n"));
    }

    static void end_SIMPLEREQ(Buffer& out)
    {
        out.append(STRLIT("</SIMPLEREQ>\n"));
    }

    static void start_IMETHODCALL(
        Buffer& out, const char* name, size_t size)
    {
        out.append(STRLIT("<IMETHODCALL NAME=\""));
        out.append(name, size);
        out.append(STRLIT("\">\n"));
    }

    static void end_IMETHODCALL(Buffer& out)
    {
        out.append(STRLIT("</IMETHODCALL>\n"));
    }

    static void put_LOCALNAMESPACEPATH(Buffer& out, const char* name_space);

    static void start_IPARAMVALUE(
        Buffer& out, const char* name, size_t size)
    {
        out.append(STRLIT("<IPARAMVALUE NAME=\""));
        out.append(name, size);
        out.append(STRLIT("\">\n"));
    }

    static void end_IPARAMVALUE(Buffer& out)
    {
        out.append(STRLIT("</IPARAMVALUE>\n"));
    }

    static void put_CLASSNAME(Buffer& out, const char* name)
    {
        out.append(STRLIT("<CLASSNAME NAME=\""));
        out.appends(name);
        out.append(STRLIT("\"/>\n"));
    }
};

CIMPLE_NAMESPACE_END

#endif /* _brevity_CIMXML_h */
