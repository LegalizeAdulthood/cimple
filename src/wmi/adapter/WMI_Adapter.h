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

#ifndef _WMI_Adapter_h
#define _WMI_Adapter_h

#include <cimple/cimple.h>
#include <cimple/Provider_Handle.h>
#include <wbemprov.h>
#include "log.h"
#pragma comment(lib, "wbemuuid.lib")

CIMPLE_NAMESPACE_BEGIN

// Disable the rpcsal annotation headers until
// we figure out if we need them
#ifdef USE_RPCSAL
#include <Rpcsal.h>
#else
#define __RPC__in
#define __RPC__out
#endif

class __declspec(dllexport) WMI_Adapter : 
    public IWbemServices,
    public IWbemProviderInit,
    public IWbemEventProvider,
    public IWbemEventProviderQuerySink
{
public:

    WMI_Adapter(
        Registration* reg,
        BSTR objectPath = NULL,
        BSTR user = NULL,
        BSTR password = NULL,
        IWbemContext* context = NULL);

    ~WMI_Adapter();

    STDMETHODIMP QueryInterface(REFIID, LPVOID*);

    STDMETHODIMP_(ULONG) AddRef();

    STDMETHODIMP_(ULONG) Release();

    HRESULT STDMETHODCALLTYPE Initialize(
        LPWSTR user,
        LONG flags,
        LPWSTR nameSpace,
        LPWSTR locale,
        IWbemServices* services,
        IWbemContext* context,
        IWbemProviderInitSink* initSink);

    HRESULT STDMETHODCALLTYPE OpenNamespace( 
        const BSTR name_spaceName,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemServices __RPC_FAR* __RPC_FAR* services,
        IWbemCallResult __RPC_FAR* __RPC_FAR* result) 
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE CancelAsyncCall( 
        IWbemObjectSink __RPC_FAR* objectSink)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE QueryObjectSink( 
        long flags,
        IWbemObjectSink __RPC_FAR* __RPC_FAR* objectSink)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE GetObject( 
        const BSTR objectPath,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemClassObject __RPC_FAR* __RPC_FAR* classObject,
        IWbemCallResult __RPC_FAR* __RPC_FAR* callResult)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE GetObjectAsync( 
        const BSTR objectPath,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);
        
    HRESULT STDMETHODCALLTYPE PutClass( 
        IWbemClassObject __RPC_FAR* classObject,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemCallResult __RPC_FAR* __RPC_FAR* callResult) 
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE PutClassAsync( 
        IWbemClassObject __RPC_FAR* classObject,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE DeleteClass( 
        const BSTR className,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemCallResult __RPC_FAR* __RPC_FAR* callResult)
    {
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE DeleteClassAsync( 
        const BSTR className,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink)
    {
        return WBEM_E_NOT_SUPPORTED;
    }
        
    HRESULT STDMETHODCALLTYPE CreateClassEnum( 
        const BSTR Superclass,
        long flags,
        IWbemContext __RPC_FAR* context,
        IEnumWbemClassObject __RPC_FAR* __RPC_FAR* ppEnum)
    {
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE CreateClassEnumAsync( 
        const BSTR Superclass,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink)
    {
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE PutInstance( 
        IWbemClassObject __RPC_FAR* instance,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemCallResult __RPC_FAR* __RPC_FAR* callResult)
    {
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE PutInstanceAsync( 
        IWbemClassObject __RPC_FAR* instance,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);
    
    HRESULT STDMETHODCALLTYPE DeleteInstance( 
        const BSTR ObjectPath,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemCallResult __RPC_FAR* __RPC_FAR* callResult)
    {
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE DeleteInstanceAsync( 
        const BSTR objectPath,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);
    
    HRESULT STDMETHODCALLTYPE CreateInstanceEnum( 
        const BSTR className,
        long flags,
        IWbemContext __RPC_FAR* context,
        IEnumWbemClassObject __RPC_FAR* __RPC_FAR* enumObject)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
    
#if 0
    HRESULT STDMETHODCALLTYPE CreateInstanceEnumAsync(
        const BSTR className,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);
#else
    HRESULT STDMETHODCALLTYPE CreateInstanceEnumAsync(
        const BSTR className,
        LONG flags,
        IWbemContext* context,
        IWbemObjectSink* objectSink);
#endif
    
    HRESULT STDMETHODCALLTYPE ExecQuery(
        const BSTR queryLanguage,
        const BSTR query,
        long flags,
        IWbemContext __RPC_FAR* context,
        IEnumWbemClassObject __RPC_FAR* __RPC_FAR* enumObject)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE ExecQueryAsync(
        const BSTR queryLanguage,
        const BSTR query,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);
    
    HRESULT STDMETHODCALLTYPE ExecNotificationQuery( 
        const BSTR queryLanguage,
        const BSTR query,
        long flags,
        IWbemContext __RPC_FAR* context,
        IEnumWbemClassObject __RPC_FAR* __RPC_FAR* enumObject)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE ExecNotificationQueryAsync( 
        const BSTR queryLanguage,
        const BSTR query,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink)
    {
        LOG_ENTER;
        return WBEM_E_NOT_SUPPORTED;
    }
    
    HRESULT STDMETHODCALLTYPE ExecMethod( 
        const BSTR,
        const BSTR,
        long,
        IWbemContext*,
        IWbemClassObject*,
        IWbemClassObject**,
        IWbemCallResult**)
    {
        return WBEM_E_NOT_SUPPORTED;
    }

    HRESULT STDMETHODCALLTYPE ExecMethodAsync( 
        const BSTR,
        const BSTR,
        long, 
        IWbemContext*,
        IWbemClassObject*,
        IWbemObjectSink*);

    HRESULT STDMETHODCALLTYPE NewQuery(
        unsigned long id,
        __RPC__in WBEM_WSTR queryLanguage,
        __RPC__in WBEM_WSTR query);

    HRESULT STDMETHODCALLTYPE CancelQuery(
        unsigned long id);

    HRESULT STDMETHODCALLTYPE ProvideEvents(
        IWbemObjectSink *handler,
        long lFlags);

    // Number of instances of this class currently allocated.
    static long numInstances;

    static long lock;

private:

    long _refs;
    Registration* _reg;
    IWbemServices* _services;
    Array<Provider_Handle*> _handles;

    size_t _numQueries;

    Provider_Handle* _find_handle(const String& class_name);

    HRESULT _create_instance(
        IWbemClassObject __RPC_FAR* instance,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);

    HRESULT _modify_instance(
        IWbemClassObject __RPC_FAR* instance,
        long flags,
        IWbemContext __RPC_FAR* context,
        IWbemObjectSink __RPC_FAR* objectSink);
};

CIMPLE_NAMESPACE_END

#endif /* _WMI_Adapter_h */
