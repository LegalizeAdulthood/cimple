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
#include "GidgetProvider.h"
#include "GidgetProviderFactory.h"
#include "log.h"

GidgetProviderFactory::GidgetProviderFactory() : _refs(0)
{
    TRACE;
}

GidgetProviderFactory::~GidgetProviderFactory()
{
    TRACE;
}


STDMETHODIMP GidgetProviderFactory::QueryInterface(
    REFIID riid, 
    LPVOID* ptr)
{
    TRACE;
    *ptr = NULL;

    if (riid == IID_IUnknown || riid == IID_IClassFactory)
    {
        *ptr = this;
        ((LPUNKNOWN)*ptr)->AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) GidgetProviderFactory::AddRef()
{
    TRACE;
    return ++_refs;
}

STDMETHODIMP_(ULONG) GidgetProviderFactory::Release()
{
    TRACE;
    ULONG n = InterlockedDecrement(&_refs);

    if (n == 0)
        delete this;
    
    return n;
}

STDMETHODIMP GidgetProviderFactory::CreateInstance(
    LPUNKNOWN outer, 
    REFIID riid, 
    LPVOID* ptr)
{
    TRACE;
    *ptr = NULL;

    if (outer)
        return CLASS_E_NOAGGREGATION;

    GidgetProvider* gidgetProvider = new GidgetProvider();

    if (!gidgetProvider)
        return E_OUTOFMEMORY;

    HRESULT hr = gidgetProvider->QueryInterface(riid, ptr);

log("[%p][%p]\n", *ptr, gidgetProvider);

    if (FAILED(hr))
    {
log("FAILED\n");
        delete gidgetProvider;
    }
    else
    {
log("NOT FAILED\n");
    }

    return hr;
}

STDMETHODIMP GidgetProviderFactory::LockServer(BOOL lock)
{
    TRACE;
    if (lock)
        InterlockedIncrement(&GidgetProvider::lock);
    else
        InterlockedDecrement(&GidgetProvider::lock);

    return NOERROR;
}
