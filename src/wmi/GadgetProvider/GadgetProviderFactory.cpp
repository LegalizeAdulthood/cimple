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
#include "GadgetProvider.h"
#include "GadgetProviderFactory.h"
#include "log.h"

GadgetProviderFactory::GadgetProviderFactory() : _refs(0)
{
}

GadgetProviderFactory::~GadgetProviderFactory()
{
}


STDMETHODIMP GadgetProviderFactory::QueryInterface(
    REFIID riid, 
    LPVOID* ptr)
{
    *ptr = NULL;

    if (riid == IID_IUnknown || riid == IID_IClassFactory)
    {
        *ptr = this;
        ((LPUNKNOWN)*ptr)->AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) GadgetProviderFactory::AddRef()
{
    return ++_refs;
}

STDMETHODIMP_(ULONG) GadgetProviderFactory::Release()
{
    ULONG n = InterlockedDecrement(&_refs);

    if (n == 0)
        delete this;
    
    return n;
}

STDMETHODIMP GadgetProviderFactory::CreateInstance(
    LPUNKNOWN outer, 
    REFIID riid, 
    LPVOID* ptr)
{
    *ptr = NULL;

    if (outer)
        return CLASS_E_NOAGGREGATION;

    GadgetProvider* gadgetProvider = new GadgetProvider();

    if (!gadgetProvider)
        return E_OUTOFMEMORY;

    HRESULT hr = gadgetProvider->QueryInterface(riid, ptr);

    if (FAILED(hr))
        delete gadgetProvider;

    return hr;
}

STDMETHODIMP GadgetProviderFactory::LockServer(BOOL lock)
{
    if (lock)
        InterlockedIncrement(&GadgetProvider::lock);
    else
        InterlockedDecrement(&GadgetProvider::lock);

    return NOERROR;
}
