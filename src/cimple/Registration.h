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

#ifndef _cimple_Registration_h
#define _cimple_Registration_h

#include "Provider.h"

#if defined(CIMPLE_WMI_MODULE)
# include <objbase.h>
# include <initguid.h>
#endif

//==============================================================================
//
// CIMPLE adapter entry point (all CIMPLE adapters implement this interface).
// The only pre-defined operation is 'T', which returns the provider type
// which (so far) is one of the following:
//
//     'P' - Pegasus C++ Provider
//     'C' - CMPI Provider
//     'W' - WMI Provider
//
//==============================================================================

CIMPLE_NAMESPACE_BEGIN

struct CIMPLE_CIMPLE_LINKAGE Registration
{
    const char* module_name;
    const char* provider_name;
    Provider_Proc provider_proc;
    const Meta_Class* meta_class;
    Registration* next;

    Registration(
        const char* module_name_,
        const char* provider_name_, 
        Provider_Proc provider_proc_,
        const Meta_Class* meta_class_,
        Registration*& next_);
};

inline Registration::Registration(
    const char* module_name_,
    const char* provider_name_, 
    Provider_Proc provider_proc_,
    const Meta_Class* meta_class_,
    Registration*& next_)
{
    provider_name = provider_name_;
    module_name = module_name_;
    provider_proc = provider_proc_;
    meta_class = meta_class_;
    next = next_;

    // Prepend to registration list:
    next_ = this;
}

typedef Registration* (*Module_Proc)();

CIMPLE_NAMESPACE_END

//==============================================================================
//
// CIMPLE registation macros
//
//==============================================================================

#define CIMPLE_MODULE(MODULE) \
    static cimple::Registration* _cimple_registration_head = 0; \
    static const char* _cimple_module_name = #MODULE; \
    extern "C" CIMPLE_EXPORT cimple::Registration* cimple_module() \
        { return _cimple_registration_head; }

#define CIMPLE_PROVIDER(PROVIDER) \
    static cimple::Registration _cimple_registration_##PROVIDER( \
        _cimple_module_name, \
        #PROVIDER, \
        cimple::PROVIDER::proc, \
        &cimple::PROVIDER::Class::static_meta_class, \
        _cimple_registration_head); \

#define CIMPLE_INSTANCE_PROVIDER(PROVIDER) \
    static cimple::Registration _cimple_registration_##PROVIDER( \
        _cimple_module_name, \
        #PROVIDER, \
        __cimple_##PROVIDER##_proc, \
        &cimple::PROVIDER::Class::static_meta_class, \
        _cimple_registration_head);

#define CIMPLE_ASSOCIATION_PROVIDER(PROVIDER) \
    static cimple::Registration _cimple_registration_##PROVIDER( \
        _cimple_module_name, \
        #PROVIDER, \
        __cimple_##PROVIDER##_proc, \
        &cimple::PROVIDER::Class::static_meta_class, \
        _cimple_registration_head); \

#define CIMPLE_INDICATION_PROVIDER(PROVIDER) \
    static cimple::Registration _cimple_registration_##PROVIDER( \
        _cimple_module_name, \
        #PROVIDER, \
        __cimple_##PROVIDER##_proc, \
        &cimple::PROVIDER::Class::static_meta_class, \
        _cimple_registration_head); \

//==============================================================================
//
// Pegasus provider entry point macro.
//
//==============================================================================

#define CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT \
    extern "C" int cimple_pegasus_adapter( \
        void* arg0, void* arg1, void* arg2, void* arg3, \
        void* arg4, void* arg5, void* arg6, void* arg7); \
    extern "C" CIMPLE_EXPORT void* PegasusCreateProvider(void* arg) \
    { \
        void* adapter = 0; \
        cimple_pegasus_adapter( \
            (void*)'P', arg, _cimple_registration_head, &adapter, 0, 0, 0, 0); \
        return adapter; \
    }

//==============================================================================
//
// OpenWBEM provider entry point macro.
//
//==============================================================================

#define CIMPLE_OPENWBEM_PROVIDER(module) \
    extern "C" CIMPLE_EXPORT const char* \
    getOWVersion()  {  return OW_VERSION;  } \
    extern "C" int cimple_openwbem_adapter( \
        void* arg0, void* arg1, void* arg2, void* arg3,  \
        void* arg4, void* arg5, void* arg6, void* arg7); \
    extern "C" CIMPLE_EXPORT OW_NAMESPACE::CppProviderBaseIFC* \
    createProvider##module() \
    { \
        OW_NAMESPACE::CppProviderBaseIFC* createProvider##module(); \
        OW_NAMESPACE::CppProviderBaseIFC* adapter = 0; \
        cimple_openwbem_adapter( \
            (void*)'O', (void*)#module, _cimple_registration_head, \
                &adapter, 0, 0, 0, 0); \
        return adapter; \
    }

//==============================================================================
//
// CMPI provider entry point macros.
//
//==============================================================================

// This structure defines enough space for all static data needed to lay down
// CMPI MI and MIFT structures.
struct __CMPI_Static_Data
{
    union
    {
        double align;
        char data[2048];
    };
};

#define __CIMPLE_CMPI_PROVIDER(TYPE,TYPE_NAME,PROVIDER) \
    extern "C" int cimple_cmpi_adapter( \
        void* arg0, void* arg1, void* arg2, void* arg3, \
        void* arg4, void* arg5, void* arg6, void* arg7); \
    extern "C" CIMPLE_EXPORT void* PROVIDER##_Create_##TYPE_NAME##MI( \
        void* cmpi_broker, \
        void* cmpi_context, \
        void* cmpi_status) \
    { \
        void* _mi = 0; \
        cimple_cmpi_adapter( \
            (void*)'C', \
            (void*)&_cmpi_static_data##PROVIDER, \
            (void*)&_cimple_registration_##PROVIDER, \
            (void*)cmpi_broker, \
            (void*)cmpi_context, \
            (void*)#PROVIDER, \
            (void*)TYPE, \
            (void*)&_mi); \
        return _mi; \
    }

#define CIMPLE_CMPI_INSTANCE_PROVIDER(PROVIDER)  \
    static __CMPI_Static_Data _cmpi_static_data##PROVIDER; \
    __CIMPLE_CMPI_PROVIDER('I', Instance, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('M', Method, PROVIDER)

#define CIMPLE_CMPI_ASSOCIATION_PROVIDER(PROVIDER)  \
    static __CMPI_Static_Data _cmpi_static_data##PROVIDER; \
    __CIMPLE_CMPI_PROVIDER('I', Instance, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('M', Method, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('A', Association, PROVIDER)

#define CIMPLE_CMPI_INDICATION_PROVIDER(PROVIDER)  \
    static __CMPI_Static_Data _cmpi_static_data##PROVIDER; \
    __CIMPLE_CMPI_PROVIDER('M', Method, PROVIDER) \
    __CIMPLE_CMPI_PROVIDER('N', Indication, PROVIDER)

// These entry points are for brokers that use the classname
// as the provider name.

#define __CIMPLE_CMPI_PROVIDER2(TYPE,TYPE_NAME,PROVIDER,CLASS) \
    extern "C" CIMPLE_EXPORT void* CLASS##_Create_##TYPE_NAME##MI( \
        void* cmpi_broker, \
        void* cmpi_context, \
        void* cmpi_status) \
    { \
        return PROVIDER##_Create_##TYPE_NAME##MI( \
            cmpi_broker, \
            cmpi_context,  \
            cmpi_status); \
    }

#define CIMPLE_CMPI_INSTANCE_PROVIDER2(PROVIDER,CLASS)  \
    __CIMPLE_CMPI_PROVIDER2('I', Instance, PROVIDER, CLASS) \
    __CIMPLE_CMPI_PROVIDER2('M', Method, PROVIDER, CLASS)

#define CIMPLE_CMPI_ASSOCIATION_PROVIDER2(PROVIDER, CLASS)  \
    __CIMPLE_CMPI_PROVIDER2('I', Instance, PROVIDER, CLASS) \
    __CIMPLE_CMPI_PROVIDER2('M', Method, PROVIDER, CLASS) \
    __CIMPLE_CMPI_PROVIDER2('A', Association, PROVIDER, CLASS)

#define CIMPLE_CMPI_INDICATION_PROVIDER2(PROVIDER, CLASS)  \
    __CIMPLE_CMPI_PROVIDER2('M', Method, PROVIDER, CLASS) \
    __CIMPLE_CMPI_PROVIDER2('N', Indication, PROVIDER, CLASS)

//==============================================================================
//
// WMI provider entry point macros
//
//==============================================================================

#if defined(CIMPLE_WMI_MODULE)

struct WMI_DllMain_Args
{
    cimple::Registration* reg;
    const char* module_name;
    const GUID* guid;
    HMODULE* module;
    HINSTANCE instance;
    ULONG reason;
    LPVOID reserved;
    BOOL result;
};

struct WMI_DllGetClassObject_Args
{
    cimple::Registration* reg;
    const char* module_name;
    const GUID* guid;
    HMODULE* module;
    const CLSID* clsid;
    const IID* iid;
    LPVOID* ptr;
    HRESULT result;
};

struct WMI_DllCanUnloadNow_Args
{
    cimple::Registration* reg;
    const char* module_name;
    const GUID* guid;
    HMODULE* module;
    HRESULT result;
};

struct WMI_DllRegisterServer_Args
{
    cimple::Registration* reg;
    const char* module_name;
    const GUID* guid;
    HMODULE* module;
    HRESULT result;
};

struct WMI_DllUnregisterServer_Args
{
    cimple::Registration* reg;
    const char* module_name;
    const GUID* guid;
    HMODULE* module;
    HRESULT result;
};

# define CIMPLE_WMI_PROVIDER_ENTRY_POINTS(GUID) \
    extern "C" int cimple_wmi_adapter( \
        void* arg0, void* arg1, void* arg2, void* arg3, \
        void* arg4, void* arg5, void* arg6, void* arg7); \
    static HMODULE _module; \
    BOOL WINAPI DllMain(HINSTANCE instance, ULONG reason, LPVOID reserved) \
    { \
        WMI_DllMain_Args args; \
        args.reg = _cimple_registration_head; \
        args.module_name = _cimple_module_name; \
        args.guid = &GUID; \
        args.module = &_module; \
        args.instance = instance; \
        args.reason = reason; \
        args.reserved = reserved; \
        cimple_wmi_adapter((void*)'W', (void*)'M', &args, 0, 0, 0, 0, 0); \
        return args.result; \
    } \
    STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ptr) \
    { \
        WMI_DllGetClassObject_Args args; \
        args.reg = _cimple_registration_head; \
        args.module_name = _cimple_module_name; \
        args.guid = &GUID; \
        args.module = &_module; \
        args.clsid = &clsid; \
        args.iid = &iid; \
        args.ptr = ptr; \
        cimple_wmi_adapter((void*)'W', (void*)'G', &args, 0, 0, 0, 0, 0); \
        return args.result; \
    } \
    STDAPI DllCanUnloadNow() \
    { \
        WMI_DllCanUnloadNow_Args args; \
        args.reg = _cimple_registration_head; \
        args.module_name = _cimple_module_name; \
        args.guid = &GUID; \
        args.module = &_module; \
        cimple_wmi_adapter((void*)'W', (void*)'C', &args, 0, 0, 0, 0, 0); \
        return args.result; \
    } \
    STDAPI DllRegisterServer() \
    { \
        WMI_DllRegisterServer_Args args; \
        args.reg = _cimple_registration_head; \
        args.module_name = _cimple_module_name; \
        args.guid = &GUID; \
        args.module = &_module; \
        cimple_wmi_adapter((void*)'W', (void*)'R', &args, 0, 0, 0, 0, 0); \
        return args.result; \
    } \
    STDAPI DllUnregisterServer() \
    { \
        WMI_DllUnregisterServer_Args args; \
        args.reg = _cimple_registration_head; \
        args.module_name = _cimple_module_name; \
        args.guid = &GUID; \
        args.module = &_module; \
        cimple_wmi_adapter((void*)'W', (void*)'U', &args, 0, 0, 0, 0, 0); \
        return args.result; \
    }

#else /* defined(CIMPLE_WMI_MODULE) */

# define CIMPLE_WMI_PROVIDER_ENTRY_POINTS /* empty */

#endif /* defined(CIMPLE_WMI_MODULE) */

//==============================================================================
//
// CIMPLE_CLASS_DEPENDENCY()
//
//==============================================================================

#define CIMPLE_CLASS_DEPENDENCY(CLASS) \
    const char* __class_##CLASS = "@(#)CLASS_DEPENDENCY=" #CLASS;

#endif /* _cimple_Registration_h */
