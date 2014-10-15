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

#include <cimple/cimple.h>
#include <wbemprov.h>
#include "utils.h"
#include "log.h"
#include "WMI_Thread_Context.h"
#include "WMI_Converter.h"
#include "WMI_Ref.h"
#include "BString.h"

CIMPLE_NAMESPACE_BEGIN

static IWbemServices* _connect(const char* nameSpace)
{
    HRESULT hr;

    // Create locator:

    IWbemLocator* loc = 0;
    WMI_Ref<IWbemLocator> loc_(loc);

    hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, 
        IID_IWbemLocator, (LPVOID*)&loc);
     
    if (FAILED(hr))
    {
        return 0;
    }

    // Translate nameSpace into WMI form (e.g., \\.\root\cimv2)

    String tns("\\\\.\\");

    for (; *nameSpace; nameSpace++)
    {
        tns.append(*nameSpace == '/' ? '\\' : *nameSpace);
    }

    // Create connection:

    IWbemServices* svc = 0;
    WMI_Ref<IWbemServices> svc_(svc);

    hr = loc->ConnectServer(
        BString(tns).rep(), NULL, NULL, 0, NULL, 0, 0, &svc);

    if (FAILED(hr))
    {
        return 0;
    }

    return svc_.steal();
}

static Ref<Instance> _next_instance(
    IEnumWbemClassObject* en,
    const Meta_Class* mc)
{
    IWbemClassObject* wi = 0;
    WMI_Ref<IWbemClassObject> wi_(wi);
    ULONG count = 0;

    // Get next WMI instance:

    if (en->Next(WBEM_INFINITE, 1, &wi, &count) != WBEM_S_NO_ERROR)
    {
        return Ref<Instance>();
    }

    // Convert to CIMPLE instance.

    Instance* ci = WMI_Converter::to_cimple_instance(mc, wi);

    if (!ci)
    {
        return Ref<Instance>();
    }

    return Ref<Instance>(ci);
}

WMI_Thread_Context::WMI_Thread_Context()
{
}

WMI_Thread_Context::~WMI_Thread_Context()
{
}

Thread_Context* WMI_Thread_Context::thread_create_hook(void* arg)
{
    return new WMI_Thread_Context();
}

void WMI_Thread_Context::thread_start_hook()
{
}

void WMI_Thread_Context::thread_exit_hook()
{
}

struct Instance_Enumerator_Rep
{
    IWbemServices* svc;
    IEnumWbemClassObject* en;
    const Meta_Class* mc;
    Ref<Instance> inst;
};

Instance_Enumerator_Rep* WMI_Thread_Context::instance_enumerator_create(
    const char* name_space,
    const Instance* model)
{
    HRESULT hr;

    // Check parameters:

    if (!name_space || !model)
    {
        return 0;
    }

    // Create connection:

    IWbemServices* svc = _connect(name_space);
    WMI_Ref<IWbemServices> svc_(svc);

    if (!svc)
    {
        return 0;
    }

    // Create enumeration:

    IEnumWbemClassObject* en = 0;
    WMI_Ref<IEnumWbemClassObject> en_(en);
    BString cn(model->meta_class->name);

    hr = svc->CreateInstanceEnum(cn.rep(), WBEM_FLAG_SHALLOW, NULL, &en);

    if (FAILED(hr))
    {
        return 0;
    }

    // Create enumerator:

    Instance_Enumerator_Rep* rep = new Instance_Enumerator_Rep;

    rep->svc = svc_.steal();
    rep->en = en_.steal();
    rep->mc = model->meta_class;

    // Get the first instance:

    rep->inst = _next_instance(rep->en, rep->mc);

    return (Instance_Enumerator_Rep*)rep;
}

void WMI_Thread_Context::instance_enumerator_destroy(
    Instance_Enumerator_Rep* rep)
{
    if (rep)
    {
        rep->svc->Release();
        rep->en->Release();
        delete rep;
    }
}

bool WMI_Thread_Context::instance_enumerator_more(
    Instance_Enumerator_Rep* rep)
{
    if (!rep)
        return false;

    return rep->inst.ptr() != 0;
}

void WMI_Thread_Context::instance_enumerator_next(
    Instance_Enumerator_Rep* rep)
{
    if (!rep)
        return;

    rep->inst = _next_instance(rep->en, rep->mc);
}

Ref<Instance> WMI_Thread_Context::instance_enumerator_get(
    Instance_Enumerator_Rep* rep)
{
    if (!rep)
        return Ref<Instance>();

    return rep->inst;
}

Ref<Instance> WMI_Thread_Context::get_instance(
    const char* name_space,
    const Instance* model)
{
    HRESULT hr;

    // Check parameters:

    if (!name_space || !model)
    {
        return Ref<Instance>();
    }

    // Create connection:

    IWbemServices* svc = _connect(name_space);
    WMI_Ref<IWbemServices> svc_(svc);

    if (!svc)
    {
        return Ref<Instance>();
    }

    // Create WMI object path:

    String model_path;

    if (instance_to_model_path(model, model_path) != 0)
    {
        return Ref<Instance>();
    }

    BString object_path(model_path);

    // Get WMI instance:

    IWbemClassObject* wi = 0;
    WMI_Ref<IWbemClassObject> wi_(wi);

    hr = svc->GetObject(object_path.rep(), WBEM_FLAG_RETURN_WBEM_COMPLETE,
        NULL, &wi, NULL);

    // Convert to CIMPLE instance.

    Instance* ci = WMI_Converter::to_cimple_instance(model->meta_class, wi);

    if (!ci)
    {
        return Ref<Instance>();
    }

    return Ref<Instance>(ci);
}

static int _put_instance(
    const char* name_space,
    const Instance* instance,
    LONG flags)
{
    HRESULT hr;

    // Check parameters:

    if (!name_space || !instance)
    {
        return -1;
    }

    // Create connection:

    IWbemServices* svc = _connect(name_space);
    WMI_Ref<IWbemServices> svc_(svc);

    if (!svc)
    {
        return -1;
    }

    // Get WMI class object:

    BString cn(instance->meta_class->name);

    IWbemClassObject* co = 0;
    WMI_Ref<IWbemClassObject> co_(co);

    hr = svc->GetObject(cn.rep(), 0, NULL, &co, NULL);

    if (FAILED(hr))
    {
        return -1;
    }

    // Convert CIMPLE instance to WMI instance:

    IWbemClassObject* wi = WMI_Converter::to_wmi_instance(svc, 0, instance);
    WMI_Ref<IWbemClassObject> wi_(wi);

    if (!wi)
    {
        return -1;
    }

    // Put the WMI instance:

    hr = svc->PutInstance(wi, flags, NULL, NULL);

    if (FAILED(hr))
    {
        return -1;
    }

    // Success!
    return 0;
}

int WMI_Thread_Context::create_instance(
    const char* name_space,
    const Instance* instance)
{
    return _put_instance(name_space, instance, WBEM_FLAG_CREATE_ONLY);
}

int WMI_Thread_Context::delete_instance(
    const char* name_space,
    const Instance* model)
{
    HRESULT hr;

    // Check parameters:

    if (!name_space || !model)
    {
        return -1;
    }

    // Create connection:

    IWbemServices* svc = _connect(name_space);
    WMI_Ref<IWbemServices> svc_(svc);

    if (!svc)
    {
        return -1;
    }

    // Create WMI object path:

    String model_path;

    if (instance_to_model_path(model, model_path) != 0)
    {
        return -1;
    }

    BString object_path(model_path);

    // Delete WMI instance:

    IWbemClassObject* wi = 0;
    WMI_Ref<IWbemClassObject> wi_(wi);

    hr = svc->DeleteInstance(object_path.rep(), 0, NULL, NULL);

    if (FAILED(hr))
    {
        return -1;
    }

    return 0;
}

int WMI_Thread_Context::modify_instance(
    const char* name_space,
    const Instance* instance)
{
    return _put_instance(name_space, instance, WBEM_FLAG_UPDATE_ONLY);
}

int WMI_Thread_Context::invoke_method(
    const char* name_space,
    const Instance* instance,
    Instance* meth)
{
    return -1;
}

void WMI_Thread_Context::allow_unload(bool flag)
{
    // There is no programmatic way to prevent unload of a provider.
    // Instead, the provider developer should set the "ClearAfter"
    // property of the __CacheControl instance for this provider.
}

bool WMI_Thread_Context::get_username(String& user_name)
{
    //TBD: This code incomplete so simply returns false until
    // we sort out if we have access to operation user name
    // in wmi.
    return false;
}

CIMPLE_NAMESPACE_END
