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

#ifndef _WMI_Adapter_Factory_h
#define _WMI_Adapter_Factory_h

#include <cimple/cimple.h>
#include <wbemprov.h>
#pragma comment(lib, "wbemuuid.lib")

CIMPLE_NAMESPACE_BEGIN

class WMI_Adapter_Factory : public IClassFactory
{
public:

    WMI_Adapter_Factory(Registration* reg);

    ~WMI_Adapter_Factory();

    STDMETHODIMP QueryInterface(REFIID, LPVOID*);

    STDMETHODIMP_(ULONG) AddRef();

    STDMETHODIMP_(ULONG) Release();

    STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID*);

    STDMETHODIMP LockServer(BOOL);

private:
    long _refs;
    Registration* _reg;
};

CIMPLE_NAMESPACE_END

#endif /* _WMI_Adapter_Factory_h */
