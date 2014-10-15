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

#include "utils.h"

CIMPLE_NAMESPACE_BEGIN

String bstr2str(const BSTR bstr)
{
    UINT blen = SysStringLen(bstr);
    UINT alen = SysStringByteLen(bstr);
    char buf[1024];
    char* astr;

    if (alen + 1 > sizeof(buf))
        astr = (char*)operator new(alen + 1);
    else
        astr = buf;

    memset(astr, 0, alen + 1);
    WideCharToMultiByte(CP_ACP, 0, bstr, blen, astr, alen, NULL, NULL);

    String result = astr;

    if (astr != buf)
        operator delete(astr);

    return result;
}

BSTR str2bstr(const String& str)
{
    size_t n = lstrlenA(str.c_str());
    BSTR bstr = SysAllocStringLen(NULL, n);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), n, bstr, n);
    return bstr;
}

String wstr2str(LPWSTR str)
{
    char buf[1024];
    char* astr;

    // Get length of required buffer (including null terminator).

    int alen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

    if (alen <= sizeof(buf))
        astr = buf;
    else
        astr = (char*)::operator new(alen);

    // Convert string:

    WideCharToMultiByte(CP_ACP, 0, str, -1, astr, alen, NULL, NULL);

    String result(astr);

    if (astr != buf)
        operator delete(astr);

    return result;
}

BSTR cstr2bstr(const char* cstr)
{
    size_t n = lstrlenA(cstr);
    BSTR bstr = SysAllocStringLen(NULL, n);
    MultiByteToWideChar(CP_ACP, 0, cstr, n, bstr, n);
    return bstr;
}

char* bstr2cstr(const BSTR bstr)
{
    UINT blen = SysStringLen(bstr);
    UINT clen = SysStringByteLen(bstr);
    char* cstr = new char[clen + 1];

    if (!cstr)
        return 0;

    memset(cstr, 0, clen + 1);
    WideCharToMultiByte(CP_ACP, 0, bstr, blen, cstr, clen, NULL, NULL);

    return cstr;
}

CIMPLE_NAMESPACE_END
