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

#include <objbase.h>
#include "WMI_Adapter.h"
#include "WMI_Adapter_Factory.h"
#include "log.h"

CIMPLE_NAMESPACE_BEGIN

WMI_Adapter_Factory::WMI_Adapter_Factory(Registration* reg) : 
    _refs(0), _reg(reg)
{
}

WMI_Adapter_Factory::~WMI_Adapter_Factory()
{
}


STDMETHODIMP WMI_Adapter_Factory::QueryInterface(
    REFIID riid, 
    LPVOID* ptr)
{
    LOG_ENTER;
    *ptr = NULL;

    if (riid == IID_IUnknown || riid == IID_IClassFactory)
    {
        *ptr = this;
        ((LPUNKNOWN)*ptr)->AddRef();
        LOG_EXIT;
        return NOERROR;
    }
    LOG_EXIT;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) WMI_Adapter_Factory::AddRef()
{
    return ++_refs;
}

STDMETHODIMP_(ULONG) WMI_Adapter_Factory::Release()
{
    LOG_ENTER;
    ULONG n = InterlockedDecrement(&_refs);

    if (n == 0)
        delete this;

    LOG_EXIT;
    return n;
}

STDMETHODIMP WMI_Adapter_Factory::CreateInstance(
    LPUNKNOWN outer, 
    REFIID riid, 
    LPVOID* ptr)
{
    LOG_ENTER;
    *ptr = NULL;

    if (outer)
    {
        LOG_EXIT;
        return CLASS_E_NOAGGREGATION;
    }

    WMI_Adapter* adapter = new WMI_Adapter(_reg);

    if (!adapter)
    {
        LOG_EXIT;
            return E_OUTOFMEMORY;
    }

    HRESULT hr = adapter->QueryInterface(riid, ptr);

    if (FAILED(hr))
        delete adapter;

    LOG_EXIT;
    return hr;
}

STDMETHODIMP WMI_Adapter_Factory::LockServer(BOOL lock)
{
    if (lock)
        InterlockedIncrement(&WMI_Adapter::lock);
    else
        InterlockedDecrement(&WMI_Adapter::lock);

    LOG_EXIT;
    return NOERROR;
}

CIMPLE_NAMESPACE_END
