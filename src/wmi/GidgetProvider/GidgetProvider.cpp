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

#define _WIN32_WINNT 0x0500
#include <objbase.h>
#include <process.h>
#include <strsafe.h>
#include <sddl.h>
#include "GidgetProvider.h"
#include "log.h"

//==============================================================================
//
// Local definitions
//
//==============================================================================

typedef struct 
{
   WCHAR*  key;
   long value;
}
InstDef;

static InstDef _defs[] = {{L"Red1", 1}, {L"Green2", 2}, {L"Blue3", 3}};

static size_t _numDefs = sizeof(_defs) / sizeof(InstDef);

#if 0

static char* _StrClone(const BSTR bstr)
{
    UINT blen = SysStringLen(bstr);
    UINT alen = SysStringByteLen(bstr);
    char* astr = new char[alen + 1];

    if (!astr)
        return 0;

    memset(astr, 0, alen + 1);
    WideCharToMultiByte(CP_ACP, 0, bstr, blen, astr, alen, NULL, NULL);

    return astr;
}


static bool _equal(BSTR bstr, const char* str)
{
    char* tmp = _StrClone(bstr);

    if (!tmp)
        return false;

    int r = strcmp(tmp, str);
    delete [] tmp;
    return r == 0;
}

#endif

inline bool _equal(BSTR s1, BSTR s2)
{
    TRACE;
    return CompareStringW(LOCALE_USER_DEFAULT, NORM_IGNORECASE,
        s1, wcslen(s1), s2, wcslen(s2)) == CSTR_EQUAL;
}

static SCODE _makeGidget(
    IWbemServices* nameSpace, 
    LPWSTR key, 
    long value, 
    IWbemClassObject** newInstance,
    WCHAR* className,
    IWbemContext* context)
{
    TRACE;
    SCODE sc;
    VARIANT v;

    // Allocate a new instance:

    IWbemClassObject* classObject = NULL;

    sc = nameSpace->GetObject(className, 0, context, &classObject, NULL);

    if (sc != S_OK)
        return WBEM_E_FAILED;

    sc = classObject->SpawnInstance(0, newInstance);

    classObject->Release();

    if (FAILED(sc))
        return sc;

    // Set the key property value.

    v.vt = VT_BSTR;
    v.bstrVal = SysAllocString(key);

    if (!v.bstrVal)
        return WBEM_E_OUT_OF_MEMORY;

    sc = (*newInstance)->Put(L"MyKey", 0, &v, 0);
    VariantClear(&v);

    if (FAILED(sc))
        return sc;

    // Set the number property value.

    v.vt = VT_I4;
    v.lVal = value;

    sc = (*newInstance)->Put(L"MyValue", 0, &v, 0);

    if (FAILED(sc))
        return sc;

    return S_OK;
}

static DWORD _impersonateLevel()
{
    TRACE;
    DWORD result = RPC_C_IMP_LEVEL_ANONYMOUS;
    HANDLE thr = NULL;

    BOOL status = OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, TRUE, &thr);

    if (status)
    {
        SECURITY_IMPERSONATION_LEVEL level = SecurityAnonymous;
        DWORD ret = 0;

        status = GetTokenInformation(thr, TokenImpersonationLevel,
            &level, sizeof(SECURITY_IMPERSONATION_LEVEL), &ret);

        CloseHandle(thr);

        if (status == FALSE)
        {
            result = RPC_C_IMP_LEVEL_ANONYMOUS;
        }
        else
        {
            switch (level)
            {
                case SecurityAnonymous:
                    result = RPC_C_IMP_LEVEL_ANONYMOUS;
                    break;
                case SecurityIdentification:
                    result = RPC_C_IMP_LEVEL_IDENTIFY;
                    break;
                case SecurityImpersonation:
                    result = RPC_C_IMP_LEVEL_IMPERSONATE;
                    break;
                case SecurityDelegation:
                    result = RPC_C_IMP_LEVEL_DELEGATE;
                    break;
                default:
                    result = RPC_C_IMP_LEVEL_ANONYMOUS;
                    break;
            }
        }
    }
    else
    {
        ULONG error = GetLastError();

        if (error == ERROR_NO_IMPERSONATION_TOKEN || error == ERROR_NO_TOKEN)
            result = RPC_C_IMP_LEVEL_DELEGATE;
        else if (error == ERROR_CANT_OPEN_ANONYMOUS)
            result = RPC_C_IMP_LEVEL_ANONYMOUS;
        else
            result = RPC_C_IMP_LEVEL_ANONYMOUS;
    }

    return result;
}

//==============================================================================
//
// class GidgetProvider
//
//==============================================================================

long GidgetProvider::numInstances = 0L;
long GidgetProvider::lock = 0L;

GidgetProvider::GidgetProvider(
    BSTR objectPath,
    BSTR user,
    BSTR password,
    IWbemContext* context) : _refs(0), _nameSpace(0)
{
    TRACE;
    InterlockedIncrement(&GidgetProvider::numInstances);
}

GidgetProvider::~GidgetProvider()
{
    TRACE;
    if (_nameSpace)
        _nameSpace->Release();

    InterlockedDecrement(&GidgetProvider::numInstances);
}

STDMETHODIMP GidgetProvider::QueryInterface(REFIID riid, LPVOID* ptr)
{
    TRACE;
    log("GidgetProvider::QueryInterface()\n");

    if (riid == IID_IWbemServices)
    {
       *ptr = (IWbemServices*)this;

       AddRef();

log("START...\n");

       return NOERROR;
    }
    else if (riid == IID_IUnknown || riid == IID_IWbemProviderInit)
    {
       *ptr = (IWbemProviderInit*)this;

       AddRef();
       return NOERROR;
    }
    
    *ptr = NULL;
    return E_NOINTERFACE;
}


STDMETHODIMP_(ULONG) GidgetProvider::AddRef()
{
    TRACE;
    return ++_refs;
}

STDMETHODIMP_(ULONG) GidgetProvider::Release()
{
    TRACE;
    ULONG n = InterlockedDecrement(&_refs);

    if (n == 0)
        delete this;
    
    return n;
}

STDMETHODIMP GidgetProvider::Initialize(
    LPWSTR user, 
    LONG flags,
    LPWSTR nameSpaceName, 
    LPWSTR locale,
    IWbemServices* nameSpace, 
    IWbemContext* context,
    IWbemProviderInitSink* initSink)
{
    TRACE;
    if (!nameSpace)
    {
        initSink->SetStatus(WBEM_E_FAILED, 0);
    }
    else
    {
        _nameSpace = nameSpace;
        _nameSpace->AddRef();
        initSink->SetStatus(WBEM_S_INITIALIZED, 0);
    }

log("GREAT\n");
    return WBEM_S_NO_ERROR;
}

#if 0
SCODE GidgetProvider::CreateInstanceEnumAsync(
    const BSTR className,
    long flags,
    IWbemContext* context,
    IWbemObjectSink FAR* handler)
#else
HRESULT GidgetProvider::CreateInstanceEnumAsync(
    const BSTR className,
    long flags,
    IWbemContext __RPC_FAR* context,
    IWbemObjectSink __RPC_FAR* handler)
#endif
{
    TRACE;

    // Check credentials:

    HRESULT hr = CoImpersonateClient();

    if (FAILED(hr))
    {
        handler->SetStatus(0, hr, NULL, NULL);
        return hr;
    }

    if (_impersonateLevel() < RPC_C_IMP_LEVEL_IMPERSONATE)
    {
        CoRevertToSelf();
        hr = WBEM_E_ACCESS_DENIED;
        handler->SetStatus(0, hr, NULL, NULL);
        return hr;
    }
  
    // Check parameters:

    if (!handler || !_nameSpace)
    {
        return WBEM_E_INVALID_PARAMETER;
    }

    if (_equal(className, L"Gidget"))
    {
        for (size_t i = 0; i < _numDefs; i++)
        {
            IWbemClassObject FAR* newInstance = NULL;

            SCODE sc = _makeGidget(
                _nameSpace, 
                _defs[i].key,
                _defs[i].value, 
                &newInstance, 
                className, 
                context);
     
            if (sc != S_OK)
            {
                handler->SetStatus(0,sc,NULL, NULL);
                return sc;
            }

            handler->Indicate(1, &newInstance);
            newInstance->Release();
        }
    }

    // Set status

    handler->SetStatus(0, S_OK, NULL, NULL);
    return S_OK;
}


SCODE GidgetProvider::GetObjectAsync(
    const BSTR objectPath,
    long flags,
    IWbemContext* context,
    IWbemObjectSink FAR* handler)
{
    TRACE;
    // Check credentials:

    HRESULT hr = CoImpersonateClient();

    if (FAILED(hr))
    {
        handler->SetStatus(0, hr, NULL, NULL);
        return hr ;
    }   

    if (_impersonateLevel() == RPC_C_IMP_LEVEL_IDENTIFY)
    {
        hr = WBEM_E_ACCESS_DENIED;
        handler->SetStatus(0 , hr , NULL , NULL);
        return hr ;
    }

    // Check parameters:

    if(!objectPath || !handler || !_nameSpace)
        return WBEM_E_INVALID_PARAMETER;

    // Get the instance:

    IWbemClassObject FAR* object;
    SCODE sc = _GetByPath(objectPath, &object, context);

    if (sc != S_OK)
    {
        handler->SetStatus(0, WBEM_E_NOT_FOUND, NULL, NULL);
        return WBEM_E_NOT_FOUND;
    }

    handler->Indicate(1, &object);
    object->Release();

    handler->SetStatus(0, S_OK, NULL, NULL);
    return S_OK;
}

SCODE GidgetProvider::_GetByPath(
    BSTR objectPath,
    IWbemClassObject FAR* FAR* object,
    IWbemContext* context)
{
    TRACE;
    SCODE sc = S_OK;

    // Do a simple path parse.  The path looks like
    // Gidget.MyKey="a"
    // Create a test string with just the part between quotes.

    WCHAR wcTest[MAX_PATH+1];
    memset(wcTest, NULL, sizeof(wcTest));
    StringCbCopyW(wcTest, sizeof(wcTest), objectPath);

    WCHAR * pwcTest, * pwcCompare = NULL;
    int iNumQuotes = 0;
    for (pwcTest = wcTest; *pwcTest; pwcTest++)
    {
        if (*pwcTest == L'\"')
        {
            iNumQuotes++;
            if (iNumQuotes == 1)
            {
                pwcCompare = pwcTest+1;
            }
            else if (iNumQuotes == 2)
            {
                *pwcTest = NULL;
                break;
            }
        }
        else if (*pwcTest == L'.')
            *pwcTest = NULL;    // isolate the class name.
    }

    if (iNumQuotes != 2)
        return WBEM_E_FAILED;

    // check the instance list for a match.

    for (size_t i = 0; i < _numDefs; i++)
    {
        if (!_wcsicmp(_defs[i].key, pwcCompare))
        {
            sc = _makeGidget(_nameSpace,_defs[i].key,
                _defs[i].value, object, wcTest, context);
            return sc;
        }
    }

    return WBEM_E_NOT_FOUND;
}
