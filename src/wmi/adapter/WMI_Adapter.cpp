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
#include <cimple/cimple.h>
#include <cimple/config.h>
//#include <cimple/log.h>
#include <initguid.h>
#include <objbase.h>
#include <cctype>
#include <process.h>
#include <strsafe.h>
#include <sddl.h>
#include "WMI_Adapter.h"
#include "WMI_Adapter_Factory.h"
#include "WMI_Containers.h"
#include "WMI_Converter.h"
#include "WMI_Thread_Context.h"
#include "log.h"
#include "Variant.h"
#include "utils.h"
#include "WMI_Ref.h"
#include "BString.h"

//void __exit()
//{
//    log(LL_DBG, file, line, "enter: %s()", func);
//}
#define RETURN_CODE(HANDLER, ERROR) \
    do \
    { \
        HRESULT __hr__ = (ERROR); \
        (HANDLER)->SetStatus(WBEM_STATUS_COMPLETE, __hr__, NULL, NULL); \
        return __hr__; \
    } \
    while (0)

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// Local definitions
//
//==============================================================================

class Impersonator
{
public:

    Impersonator()
    {
        CoImpersonateClient();
    }

    ~Impersonator()
    {
        CoRevertToSelf();
    }
};

static void _formatGUID(REFGUID guid, char str[128])
{
    LOG_ENTER;
    WCHAR wstr[128];
    memset(wstr, NULL, sizeof(wstr));

    StringFromGUID2(guid, wstr, sizeof(wstr) / sizeof(wstr[0]));

    memset(str, 0, 128);
    wcstombs(str, wstr, 128);
}

static void _formatCLSID(REFGUID guid, char clsid[128])
{
    char str[128];
    LOG_ENTER;
    _formatGUID(guid, str);
    StringCbCopy(clsid, 128, "Software\\classes\\CLSID\\");
    StringCbCat(clsid, 128, (LPCTSTR)str);
}

static HRESULT _registerServer(
    const GUID* guid,
    HMODULE mod,
    const char* serverName,
    const char* threadingModel)
{
    char clsid[128];
    char module[MAX_PATH + 1];
    HKEY key1;
    HKEY key2;
    LONG r;

    LOG_ENTER;
    // Format CLSID path: "Software\\classes\\CLSID\{GUID}"

    _formatCLSID(*guid, clsid);

    // Create "Software\\classes\\CLSID\{GUID}\InprocServer32"

    r = RegCreateKeyEx(HKEY_LOCAL_MACHINE, clsid, 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key1, NULL );

    if (r != ERROR_SUCCESS)
    {
        LOG_EXIT;
        return E_FAIL;
    }

    r = RegSetValueEx(key1, NULL, 0, REG_SZ, (BYTE*)serverName,
        strlen(serverName) + 1);

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key1);
        LOG_EXIT;
        return E_FAIL;
    }

    r = RegCreateKeyEx(key1, "InprocServer32", 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key2, NULL );

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key1);
        LOG_EXIT;
        return E_FAIL;
    }

    memset(&module, NULL, sizeof(module));
    GetModuleFileName(mod, module, sizeof(module) / sizeof(char) - 1);

    r = RegSetValueEx(key2, NULL, 0, REG_SZ, (BYTE*)module, strlen(module)+1);

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key2);
        RegCloseKey(key1);
        LOG_EXIT;
        return E_FAIL;
    }

    // Create "Software\\classes\\CLSID\{GUID}\InprocServer32\ThreadingModel"
    
    r = RegSetValueEx(key2, "ThreadingModel", 0, REG_SZ, (BYTE*)threadingModel,
        strlen(threadingModel)+1);

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key2);
        RegCloseKey(key1);
        LOG_EXIT;
        return E_FAIL;
    }

    RegCloseKey(key1);
    RegCloseKey(key2);

    LOG_EXIT;
    return NOERROR;
}

static HRESULT _unregisterServer(const GUID* guid)
{
    char clsidstr[128];
    char guidstr[128];
    HKEY key;
    DWORD r;

    LOG_ENTER;
    // Format GUID path:

    _formatGUID(*guid, guidstr);

    // Format CLSID path: "Software\\classes\\CLSID\{GUID}"

    _formatCLSID(*guid, clsidstr);

    // Delete "Software\\classes\\CLSID\{GUID}\InProcServer32 key.

    r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, clsidstr, 0, KEY_WRITE, &key);

    if (r == NO_ERROR)
    {
        RegDeleteKey(key, "InProcServer32");
        RegCloseKey(key);
    }

    // Delete "Software\\classes\\CLSID\{GUID} key.

    r = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "Software\\classes\\CLSID", 0, KEY_WRITE, &key);

    if (r == NO_ERROR)
    {
        RegDeleteKey(key, guidstr);
        RegCloseKey(key);
    }

    LOG_EXIT;
    return NOERROR;
}

static int _get_classname(IWbemClassObject* co, String& classname)
{
    LOG_ENTER;
    classname.clear();

    BString nm(L"__CLASS", WSTR_TAG);
    VARIANT v;
    HRESULT hr = co->Get(nm.rep(), 0, &v, 0, 0);

    if (!SUCCEEDED(hr) || V_VT(&v) != VT_BSTR)
    {
        VariantClear(&v);
        LOG_EXIT;
        return -1;
    }

    classname = bstr2str(V_BSTR(&v));
    VariantClear(&v);
    LOG_EXIT;
    return 0;
}

//==============================================================================
//
// class WMI_Adapter
//
//==============================================================================

long WMI_Adapter::numInstances = 0L;
long WMI_Adapter::lock = 0L;

WMI_Adapter::WMI_Adapter(
    Registration* reg,
    BSTR objectPath,
    BSTR user,
    BSTR password,
    IWbemContext* context) : _refs(0), _reg(reg), _services(0)
{
    LOG_ENTER;
    WMI_Thread_Context_Pusher pusher;

    InterlockedIncrement(&WMI_Adapter::numInstances);

    for (Registration* p = reg; p; p = p->next)
    {
        Provider_Handle* h = new Provider_Handle(p);
        h->load();
        _handles.append(h);
    }
    LOG_EXIT;
}

WMI_Adapter::~WMI_Adapter()
{
    WMI_Thread_Context_Pusher pusher;

    LOG_ENTER;

    for (size_t i = 0; i < _handles.size(); i++)
    {
        _handles[i]->unload();
        delete _handles[i];
    }

    if (_services)
        _services->Release();

    InterlockedDecrement(&WMI_Adapter::numInstances);
    LOG_EXIT;
}

static void _print_guid(REFIID riid, char buf[1024])
{
    char* p = buf;
    int n;

    n = sprintf(p, "%08X-", riid.Data1);
    p += n;

    n = sprintf(p, "%04X-", riid.Data2);
    p += n;

    n = sprintf(p, "%04X-", riid.Data3);
    p += n;

    for (int i = 0; i < 2; i++)
    {
        n = sprintf(p, "%02X", riid.Data4[i]);
        p += n;
    }

    n = sprintf(p, "-");
    p += n;

    for (int i = 2; i < 8; i++)
    {
        n = sprintf(p, "%02X", riid.Data4[i]);
        p += n;
    }
}

STDMETHODIMP WMI_Adapter::QueryInterface(REFIID riid, LPVOID* ptr)
{
    /* We must respond to all of these interfaces:
           IWbemServices
           IWbemEventProviderQuerySink
           IWbemEventProvider
           IWbemProviderInit
    */

    LOG_ENTER;

    __log("this=%p\n", this);

    //wchar buf[1024];
    //char[] str;
    //StringFromGUID2( riid, cast(wchar*)buf, buf.length );
    //for( int i = 0; buf[i] > 0; i++ )
    //{
    //    str ~= cast(char)buf[i];
    //}
    //printf( "queryif : %.*s ", str );

    if (riid == IID_IWbemServices)
    {
       *ptr = (IWbemServices*)this;
       __log("%s\n", "IwbemServices IID");
       AddRef();
       LOG_EXIT;
       return NOERROR;
    }
    else if (riid == IID_IWbemEventProviderQuerySink)
    {
       *ptr = (IWbemEventProviderQuerySink*)this;
       __log("%s\n", "IID_IWbemEventProviderQuerySink");
       AddRef();
       LOG_EXIT;
       return NOERROR;
    }
    else if (riid == IID_IWbemEventProvider)
    {
       *ptr = (IWbemEventProvider*)this;
       __log("%s\n", "IID_IWbemEventProvider");
       AddRef();
       LOG_EXIT;
       return NOERROR;
    }
    else if (riid == IID_IWbemProviderInit)
    {
       *ptr = (IWbemProviderInit*)this;

       __log("%s\n", "IID_IWbemProviderInit");
       AddRef();
       LOG_EXIT;
       return NOERROR;
    }
    else if (riid == IID_IWbemUnboundObjectSink)
    {
        __log("%s\n", "IID_IWbemUnboundObjectSink");
        *ptr = NULL;
        LOG_EXIT;
        return E_NOINTERFACE;
    }
#if 0
    else if (riid == IID_IWbemHiPerfProvider)
    {
        __log("%s\n", "IID_IWbemHiPerfProvider");
        *ptr = NULL;
        LOG_EXIT;
        return E_NOINTERFACE;
    }
    else if (riid == IID_IWbemEventConsumerProvider)
    {
        __log("%s\n", "IID_IWbemEventConsumerProvider");
        *ptr = NULL;
        LOG_EXIT;
        return E_NOINTERFACE;
    }
    /* this one undefined
    else if (riid == IID_IWbemEventConsumerProviderEx)
    {
        __log("%s\n", "IID_IWbemEventConsumerProviderEx");
        *ptr = NULL;
        LOG_EXIT;
        return E_NOINTERFACE;
    }
    */
    else if (riid == IID_IWbemEventProviderSecurity)
    {
        __log("%s\n", "IID_IWbemEventProviderSecurity");
        *ptr = NULL;
        LOG_EXIT;
        return E_NOINTERFACE;
    }
    else if (riid == IID_IWbemPropertyProvider)
    {
        __log("%s\n", "IID_IWbemEventProviderSecurity");
        *ptr = NULL;
        LOG_EXIT;
        return E_NOINTERFACE;
    }
#endif
    else if (riid == IID_IUnknown)
    {
       *ptr = (IWbemProviderInit*)this;
       __log("%s\n", "IID_IUnknown");

       AddRef();
       LOG_EXIT;
       return NOERROR;
    }
    
    {
        char buf[1024];
        _print_guid(riid, buf);
        __log("UNHANDLED IID: %s\n",buf);
    }

    *ptr = NULL;
    LOG_EXIT;
    return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) WMI_Adapter::AddRef()
{
    LOG_ENTER;
    return ++_refs;
    LOG_EXIT;
}

STDMETHODIMP_(ULONG) WMI_Adapter::Release()
{
    LOG_ENTER;
    ULONG n = InterlockedDecrement(&_refs);

    if (n == 0)
        delete this;

    LOG_EXIT;
    return n;
}

STDMETHODIMP WMI_Adapter::Initialize(
    LPWSTR user, 
    LONG flags,
    LPWSTR nameSpace,
    LPWSTR locale,
    IWbemServices* services, 
    IWbemContext* context,
    IWbemProviderInitSink* initSink)
{
    LOG_ENTER;
    if (!services)
    {
        initSink->SetStatus(WBEM_E_FAILED, 0);
    }
    else
    {
        _services = services;
        _services->AddRef();
        initSink->SetStatus(WBEM_S_INITIALIZED, 0);
    }

    LOG_EXIT;
    return WBEM_S_NO_ERROR;
}

struct Enum_Instances_Proc_Data
{
    const Meta_Repository* mr;
    IWbemContext* context;
    IWbemServices* services;
    BSTR class_name;
    IWbemObjectSink FAR* handler;
};

static bool _enum_instances_proc(
    Instance* inst,
    Enum_Instances_Status status,
    void* client_data)
{
    LOG_ENTER;
    Enum_Instances_Proc_Data* data = (Enum_Instances_Proc_Data*)client_data;

    if (!inst)
    {
        LOG_EXIT;
        return false;
    }

    IWbemClassObject* wi = 0;
    WMI_Ref<IWbemClassObject> wi_(wi);
    
    wi = WMI_Converter::to_wmi_instance(data->services, data->context, inst);

    if (wi)
    {
        data->handler->Indicate(1, &wi);
    }

    LOG_EXIT;
    return true;
}

HRESULT WMI_Adapter::_create_instance(
    IWbemClassObject __RPC_FAR* instance,
    long flags,
    IWbemContext __RPC_FAR* context,
    IWbemObjectSink __RPC_FAR* handler)
{
    LOG_ENTER;
    Impersonator impersonator;

    // Get the classname.

    String cn;

    if (_get_classname(instance, cn) != 0)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Lookup provider.

    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Get meta-repository from provider registration.

    const Meta_Repository* mr = 
        handle->registration()->meta_class->meta_repository;

    if (!mr)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Get meta-class:

    const Meta_Class* mc = handle->registration()->meta_class;

    if (!mc)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Convert to CIMPLE instance.

    Instance* ci = WMI_Converter::to_cimple_instance(mc, instance);

    if (!ci)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    Ref<Instance> ci_(ci);

    // Invoke provider.

    Create_Instance_Status st = handle->create_instance(ci);

    switch (st)
    {
        case CREATE_INSTANCE_OK:
        {
            RETURN_CODE(handler, WBEM_S_NO_ERROR);
        }

        case CREATE_INSTANCE_DUPLICATE:
        {
            RETURN_CODE(handler, WBEM_S_ALREADY_EXISTS);
        }

        case CREATE_INSTANCE_UNSUPPORTED:
        {
            RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);
        }

        default:
        {
            RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }

    // Unreachable!
    LOG_EXIT;
    RETURN_CODE(handler, WBEM_E_FAILED);
}

HRESULT WMI_Adapter::_modify_instance(
    IWbemClassObject __RPC_FAR* instance,
    long flags,
    IWbemContext __RPC_FAR* context,
    IWbemObjectSink __RPC_FAR* handler)
{
    LOG_ENTER;
    Impersonator impersonator;

    // Get the classname.

    String cn;

    if (_get_classname(instance, cn) != 0)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Lookup provider.

    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Get meta-repository from provider registration.

    const Meta_Repository* mr = 
        handle->registration()->meta_class->meta_repository;

    if (!mr)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Get meta-class:

    const Meta_Class* mc = handle->registration()->meta_class;

    if (!mc)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Convert to CIMPLE instance.

    Instance* ci = WMI_Converter::to_cimple_instance(mc, instance);

    if (!ci)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    Ref<Instance> ci_(ci);

    // Invoke provider.

    Modify_Instance_Status st = handle->modify_instance(ci, ci);

    switch (st)
    {
        case MODIFY_INSTANCE_OK:
        {
            RETURN_CODE(handler, WBEM_S_NO_ERROR);
        }

        case MODIFY_INSTANCE_NOT_FOUND:
        {
            RETURN_CODE(handler, WBEM_E_NOT_FOUND);
        }

        case MODIFY_INSTANCE_UNSUPPORTED:
        {
            RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);
        }

        default:
        {
            RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }

    // Unreachable!
    RETURN_CODE(handler, WBEM_E_FAILED);
}

HRESULT STDMETHODCALLTYPE WMI_Adapter::PutInstanceAsync( 
    IWbemClassObject __RPC_FAR* instance,
    long flags,
    IWbemContext __RPC_FAR* context,
    IWbemObjectSink __RPC_FAR* handler)
{
    WMI_Thread_Context_Pusher pusher;

    LOG_ENTER;
    // Dispatch to _create_instance() or _modify_instance().

    if (flags & WBEM_FLAG_CREATE_ONLY)
    {
        return _create_instance(instance, flags, context, handler);
    }
    else if (flags & WBEM_FLAG_UPDATE_ONLY)
    {
        return _modify_instance(instance, flags, context, handler);
    }
    else if (flags & WBEM_FLAG_CREATE_OR_UPDATE)
    {
        RETURN_CODE(handler, WBEM_E_PROVIDER_NOT_CAPABLE);
    }
    else
    {
        RETURN_CODE(handler, WBEM_E_INVALID_PARAMETER);
    }

    // Unrechable!
    return WBEM_E_FAILED;
}

#if 0
SCODE WMI_Adapter::CreateInstanceEnumAsync(
    const BSTR class_name,
    long flags,
    IWbemContext* context,
    IWbemObjectSink FAR* handler)
#else
HRESULT WMI_Adapter::CreateInstanceEnumAsync(
    const BSTR class_name,
    LONG flags,
    IWbemContext* context,
    IWbemObjectSink* handler)
#endif
{
    LOG_ENTER;
    WMI_Thread_Context_Pusher pusher;

    Impersonator impersonator;

    // Check parameters:

    if (!handler || !_services)
    {
        return WBEM_E_INVALID_PARAMETER;
    }

    // Find provider for this class:

    String cn(bstr2str(class_name));
    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Dispatch to provider:

    Enum_Instances_Proc_Data data;
    data.mr = _reg->meta_class->meta_repository;
    data.context = context;
    data.services = _services;
    data.handler = handler;
    data.class_name = class_name;

    Enum_Instances_Status st = handle->enum_instances(
        0, _enum_instances_proc, &data);

    switch (st)
    {
        case ENUM_INSTANCES_OK:
        {
            RETURN_CODE(handler, S_OK);
        }

        case ENUM_INSTANCES_FAILED:
        default:
        {
            RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }

    // Unreachable!
    return S_OK;
}

SCODE WMI_Adapter::GetObjectAsync(
    const BSTR objectPath,
    long flags,
    IWbemContext* context,
    IWbemObjectSink FAR* handler)
{
    WMI_Thread_Context_Pusher pusher;
    Impersonator impersonator;

    LOG_ENTER;

    // Check parameters:

    if(!objectPath || !handler || !_services)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_PARAMETER);
    }

    // Lookup provider:

    String op = bstr2str(objectPath);
    String cn = op.substr(0, op.find('.'));
    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Convert object path to model:

    Instance* model = model_path_to_instance(
        handle->registration()->meta_class, op.c_str());

    if (!model)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_OBJECT_PATH);
    }

    // Invoke provider:

    Instance* inst = 0;
    Get_Instance_Status status = handle->get_instance(model, inst);
    Ref<Instance> inst_(inst);

    switch (status)
    {
        case GET_INSTANCE_OK:
        {
            IWbemClassObject* wi = 0;
            WMI_Ref<IWbemClassObject> wi_(wi);

            wi = WMI_Converter::to_wmi_instance(_services, context, inst);

            if (wi)
            {
                handler->Indicate(1, &wi);
            }

            break;
        }

        case GET_INSTANCE_NOT_FOUND:
        {
            RETURN_CODE(handler, WBEM_E_NOT_FOUND);
        }

        case GET_INSTANCE_UNSUPPORTED:
        {
            RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);
        }

        default:
        {
            RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }

    // Unreachable!
    RETURN_CODE(handler, S_OK);
}

HRESULT WMI_Adapter::DeleteInstanceAsync( 
    const BSTR objectPath,
    long flags,
    IWbemContext __RPC_FAR* context,
    IWbemObjectSink __RPC_FAR* handler)
{
    LOG_ENTER;
    WMI_Thread_Context_Pusher pusher;
    Impersonator impersonator;

    // Check parameters:

    if(!objectPath || !handler || !_services)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_PARAMETER);
    }

    // Lookup provider:

    String op = bstr2str(objectPath);
    String cn = op.substr(0, op.find('.'));
    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Convert object path to model:

    Instance* model = model_path_to_instance(
        handle->registration()->meta_class, op.c_str());

    if (!model)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_OBJECT_PATH);
    }

    // Invoke provider:

    Instance* inst = 0;

    Delete_Instance_Status status = handle->delete_instance(model);
    Ref<Instance> inst_(inst);

    switch (status)
    {
        case DELETE_INSTANCE_OK:
            break;

        case DELETE_INSTANCE_NOT_FOUND:
            RETURN_CODE(handler, WBEM_E_NOT_FOUND);

        case DELETE_INSTANCE_UNSUPPORTED:
            RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);
    }

    RETURN_CODE(handler, S_OK);
}

//==============================================================================
//
// Parse WQL query of the form:
//
//     SELECT TOK1[,TOK2][,TOK3] FROM CLASSNAME WHERE ...
//
// For example:
//
//     select * from MyClass where ...
//
//==============================================================================

static int _parse_wql(const String& query, String& classname)
{
    LOG_ENTER;
    const char* p = query.c_str();

    // Skip whitespace:

    while (isspace(*p))
        p++;

    // Expect "select":

    if (strnicmp(p, "select", 6) != 0 || !isspace(p[6]))
    {
        return -1;
    }

    p += 7;

    // Expect field list (or "*")

    for (;;)
    {
        // Skip whitespace:

        while (isspace(*p))
            p++;

        // Skip over field name:

        while (*p && !isspace(*p) && *p != ',')
            p++;

        // Skip whitespace:

        while (isspace(*p))
            p++;

        if (*p != ',')
            break;

        p++;
    }

    // Expect "from":

    if (strnicmp(p, "from", 4) != 0 || !isspace(p[4]))
    {
        return -1;
    }

    p += 5;

    // Skip whitespace:

    while (isspace(*p))
        p++;

    // Expect classname:

    const char* start = p;

    while (*p && !isspace(*p))
        p++;

    classname.assign(start, p - start);

    return 0;
}

HRESULT WMI_Adapter::ExecQueryAsync(
    const BSTR queryLanguage,
    const BSTR queryExpression,
    long flags,
    IWbemContext __RPC_FAR* context,
    IWbemObjectSink __RPC_FAR* handler)
{
    LOG_ENTER;
    WMI_Thread_Context_Pusher pusher;

    // Reject non-wql queries.

    String lang = bstr2str(queryLanguage);

    if (lang != "WQL")
    {
        RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);
    }

    // Extract the class name from the query expression.

    String query = bstr2str(queryExpression);
    String cn;

    if (_parse_wql(query, cn) != 0)
    {
        RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);
    }

    // Find provider for this class:

    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Dispatch to provider:

    Enum_Instances_Proc_Data data;
    data.mr = _reg->meta_class->meta_repository;
    data.context = context;
    data.services = _services;
    data.handler = handler;
    BString tcn(cn);
    data.class_name = tcn.rep();

    Enum_Instances_Status st = handle->enum_instances(
        0, _enum_instances_proc, &data);

    switch (st)
    {
        case ENUM_INSTANCES_OK:
        {
            RETURN_CODE(handler, S_OK);
        }

        case ENUM_INSTANCES_FAILED:
        default:
        {
            RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }

    // Unreachable!
    return S_OK;
}

HRESULT WMI_Adapter::ExecMethodAsync( 
    const BSTR objectPath,
    const BSTR methodName,
    long flags, 
    IWbemContext* context,
    IWbemClassObject* inParams,
    IWbemObjectSink* handler)
{
    WMI_Thread_Context_Pusher pusher;
    Impersonator impersonator;
    HRESULT hr;

    LOG_ENTER;
    // Check parameters:

    if (!objectPath || !methodName || !context || !handler)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_PARAMETER);
    }

    // Lookup provider:

    String op = bstr2str(objectPath);
    String cn = op.substr(0, op.find('.'));
    Provider_Handle* handle = _find_handle(cn);

    if (!handle)
    {
        RETURN_CODE(handler, WBEM_E_INVALID_CLASS);
    }

    // Get meta-repository from handle:

    const Meta_Repository* mr = 
        handle->registration()->meta_class->meta_repository;

    if (!mr)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Find meta-class:

    const Meta_Class* mc = find_meta_class(mr, cn.c_str());

    if (!mc)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Get meta-method from meta-class:

    String mn = bstr2str(methodName);
    const Meta_Method* mm = find_method(mc, mn.c_str());

    if (!mm)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Convert to CIMPLE method instance:

    Instance* meth = 0;

    if (inParams)
    {
        WMI_Args_Container cont1(mr, inParams);

        int rc = cont1.convert((const Meta_Class*)mm, CIMPLE_FLAG_IN, meth);

        if (rc != 0 || !meth)
        {
            RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }
    else
    {
        meth = create((const Meta_Class*)mm);
    }

    // Create model (if non-static method):

    Instance* model = 0;
    Ref<Instance> model_(model);

    if (op != cn)
    {
        if (!(model = model_path_to_instance(
            handle->registration()->meta_class, op.c_str())))
        {
            RETURN_CODE(handler, WBEM_E_INVALID_OBJECT_PATH);
        }
    }

    // Invoke the method:

    Invoke_Method_Status st = handle->invoke_method(model, meth);

    if (st != INVOKE_METHOD_OK)
    {
        switch (st)
        {
            case INVOKE_METHOD_UNSUPPORTED:
                RETURN_CODE(handler, WBEM_E_NOT_SUPPORTED);

            case INVOKE_METHOD_FAILED:
                RETURN_CODE(handler, WBEM_E_FAILED);

            default:
                RETURN_CODE(handler, WBEM_E_FAILED);
        }
    }

    // Get WMI class object from namespace:

    IWbemClassObject* co = 0;
    WMI_Ref<IWbemClassObject> co_(co);

    hr = _services->GetObject(BString(cn).rep(), 0, context, &co, 0);

    if (hr != S_OK)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Get WMI method object from class object:

    IWbemClassObject* mo = 0;
    WMI_Ref<IWbemClassObject> mo_(mo);

    hr = co->GetMethod(methodName, 0, 0, &mo);

    if (hr != S_OK)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Create WMI out parameters object.

    IWbemClassObject* outParams = 0;
    WMI_Ref<IWbemClassObject> outParams_(outParams);

    hr = mo->SpawnInstance(0, &outParams);

    if (hr != S_OK)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Convert output parameters:

    WMI_Args_Container cont2(mr, outParams);

    if (cont2.convert(meth, CIMPLE_FLAG_OUT) != 0)
    {
        RETURN_CODE(handler, WBEM_E_FAILED);
    }

    // Send instance back to client!

    handler->Indicate(1, &outParams);

    RETURN_CODE(handler, S_OK);
}

HRESULT STDMETHODCALLTYPE WMI_Adapter::NewQuery(
    unsigned long id,
    __RPC__in WBEM_WSTR queryLanguage,
    __RPC__in WBEM_WSTR queryExpression)
{
    LOG_ENTER;
    _numQueries++;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE WMI_Adapter::CancelQuery(
    unsigned long id)
{
    LOG_ENTER;
    WMI_Thread_Context_Pusher pusher;

    // If no more queries left, then disable indications on all indication
    // providers.

    _numQueries--;

    if (_numQueries == 0)
    {
        for (size_t i = 0; i < _handles.size(); i++)
        {
            Provider_Handle* h = _handles[i];
            const Meta_Class* mc = h->registration()->meta_class;

            if (mc->flags & CIMPLE_FLAG_INDICATION)
            {
                h->disable_indications();
            }
        }
    }

    return S_OK;
}

struct Indication_Proc_Data
{
    IWbemServices* services;
    IWbemObjectSink* sink;
    const Meta_Class* meta_class;
    Mutex mutex;
};

static bool _indication_proc(Instance* indication, void* client_data)
{
    LOG_ENTER;
    Indication_Proc_Data* data = (Indication_Proc_Data*)client_data;
    Auto_Mutex am(data->mutex);

    // Delete client data on last call.

    if (indication == 0)
    {
        data->services->Release();
        data->sink->Release();
        delete data;
        return false;
    }

    // Prepare for indication to be destructed.

    Ref<Instance> indication_(indication);

    // Convert CIMPLE instance to WMI event instance:

    IWbemClassObject* wi = 0;
    WMI_Ref<IWbemClassObject> wi_(wi);

    wi = WMI_Converter::to_wmi_instance(data->services, 0, indication);

    if (wi)
    {
        data->sink->Indicate(1, &wi);
    }

    // Keep them coming!
    return true;
}

HRESULT WMI_Adapter::ProvideEvents(
    IWbemObjectSink* sink,
    long lFlags)
{
    LOG_ENTER;
    WMI_Thread_Context_Pusher pusher;

    // Enable indications on all indication provider:

    for (size_t i = 0; i < _handles.size(); i++)
    {
        Provider_Handle* h = _handles[i];
        const Meta_Class* mc = h->registration()->meta_class;

        if (mc->flags & CIMPLE_FLAG_INDICATION)
        {
            sink->AddRef();
            _services->AddRef();

            Indication_Proc_Data* data = new Indication_Proc_Data;
            data->services = _services;
            data->sink = sink;
            data->meta_class = mc;

            h->enable_indications(_indication_proc, data);
        }
    }

    return WBEM_S_NO_ERROR;
}

Provider_Handle* WMI_Adapter::_find_handle(const String& class_name)
{
    LOG_ENTER;
    for (size_t i = 0; i < _handles.size(); i++)
    {
        Provider_Handle* h = _handles[i];

        if (h->registration()->meta_class->name == class_name)
        {
            return h;
        }
    }

    // Not found!
    return 0;
}

CIMPLE_NAMESPACE_END

//==============================================================================
//
// Entry point defintions:
//
//==============================================================================

using namespace cimple;

static void _DllMain(WMI_DllMain_Args* args)
{
    LOG_ENTER;
    if (DLL_PROCESS_ATTACH == args->reason)
        *args->module = args->instance;

    args->result = TRUE;
    LOG_EXIT;
    return;
}

static void _DllGetClassObject(WMI_DllGetClassObject_Args* args)
{
    LOG_ENTER;
    WMI_Adapter_Factory* factory;

    if (*args->clsid != *args->guid)
    {
        args->result = E_FAIL;
        LOG_EXIT;
        return;
    }

    factory = new WMI_Adapter_Factory(args->reg);

    if (!factory)
    {
        args->result = E_OUTOFMEMORY;
        LOG_EXIT;
        return;
    }

    HRESULT hr = factory->QueryInterface(*args->iid, args->ptr);

    if (FAILED(hr))
        delete factory;

    args->result = hr;
    LOG_EXIT;
}

static void _DllCanUnloadNow(WMI_DllCanUnloadNow_Args* args)
{
    LOG_ENTER;
    if (WMI_Adapter::numInstances == 0 && WMI_Adapter::lock == 0)
        args->result = S_OK;
    else
        args->result = S_FALSE;
    LOG_EXIT;
}

static void _DllRegisterServer(WMI_DllRegisterServer_Args* args)
{
    LOG_ENTER;
    args->result = 
        _registerServer(args->guid, *args->module, args->module_name, "Both");
    LOG_EXIT;
}

static void _DllUnregisterServer(WMI_DllUnregisterServer_Args* args)
{
    LOG_ENTER;
    args->result = _unregisterServer(args->guid);
    LOG_EXIT;
}

extern "C" 
__declspec(dllexport)
int cimple_wmi_adapter( 
    void* arg0, /* 'W' */
    void* arg1, /* function */
    void* arg2, /* WMI_Static_Data */
    void* arg3, /* Registration */
    void* arg4, /* Operation-specific */
    void* arg5, /* Operation-specific */
    void* arg6, /* Operation-specific */
    void* arg7) /* Operation-specific */
{
    // Extract parameters:

    LOG_ENTER;

    long function = (long)arg1;

    // Dispatch operation:

    switch (function)
    {
        case 'M': /* DllMain() */
        {
            _DllMain((WMI_DllMain_Args*)arg2);
            return 0;
        }
        case 'G': /* DllGetClassObject() */
        {
            _DllGetClassObject((WMI_DllGetClassObject_Args*)arg2);
            return 0;
        }
        case 'C': /* DllCanUnloadNow() */
        {
            _DllCanUnloadNow((WMI_DllCanUnloadNow_Args*)arg2);
            return 0;
        }
        case 'R': /* DllRegisterServer() */
        {
            _DllRegisterServer((WMI_DllRegisterServer_Args*)arg2);
            return 0;
        }
        case 'U': /* DllUnregisterServer() */
        {
            _DllUnregisterServer((WMI_DllUnregisterServer_Args*)arg2);
            return 0;
        }
        default:
        {
            LOG_EXIT;
            return -1;
        }
    }

    LOG_EXIT;
    return 0;
}
