//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENMOD 2.0.23
//
//==============================================================================

/* NOCHKSRC */
#include <cimple/cimple.h>
#include "CMPL_Base_Provider.h"
#include "CMPL_Derived_Provider.h"
#include "CMPL_Other_Provider.h"
#include "CMPL_Assoc_Provider.h"

using namespace cimple;

static int __cimple_CMPL_Base_Provider_proc(
    const Registration* registration,
    int operation,
    void* arg0,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    typedef CMPL_Base Class;
    typedef CMPL_Base_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Instance_Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    return -1;
}

static int __cimple_CMPL_Derived_Provider_proc(
    const Registration* registration,
    int operation,
    void* arg0,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    typedef CMPL_Derived Class;
    typedef CMPL_Derived_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Instance_Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    return -1;
}

static int __cimple_CMPL_Other_Provider_proc(
    const Registration* registration,
    int operation,
    void* arg0,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    typedef CMPL_Other Class;
    typedef CMPL_Other_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Instance_Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    return -1;
}

static int __cimple_CMPL_Assoc_Provider_proc(
    const Registration* registration,
    int operation,
    void* arg0,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    typedef CMPL_Assoc Class;
    typedef CMPL_Assoc_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Association_Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    return -1;
}

CIMPLE_MODULE(/home/kschopmeyer/cimplework/pegasus/LINUX_X86_64_GNU/bin/genmod_Module);
CIMPLE_INSTANCE_PROVIDER(CMPL_Base_Provider);
CIMPLE_INSTANCE_PROVIDER(CMPL_Derived_Provider);
CIMPLE_INSTANCE_PROVIDER(CMPL_Other_Provider);
CIMPLE_ASSOCIATION_PROVIDER(CMPL_Assoc_Provider);

#ifdef CIMPLE_PEGASUS_MODULE
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifdef CIMPLE_CMPI_MODULE
  CIMPLE_CMPI_INSTANCE_PROVIDER(CMPL_Base_Provider);
  CIMPLE_CMPI_INSTANCE_PROVIDER2(CMPL_Base_Provider, CMPL_Base);
  CIMPLE_CMPI_INSTANCE_PROVIDER(CMPL_Derived_Provider);
  CIMPLE_CMPI_INSTANCE_PROVIDER2(CMPL_Derived_Provider, CMPL_Derived);
  CIMPLE_CMPI_INSTANCE_PROVIDER(CMPL_Other_Provider);
  CIMPLE_CMPI_INSTANCE_PROVIDER2(CMPL_Other_Provider, CMPL_Other);
  CIMPLE_CMPI_ASSOCIATION_PROVIDER(CMPL_Assoc_Provider);
  CIMPLE_CMPI_ASSOCIATION_PROVIDER2(CMPL_Assoc_Provider, CMPL_Assoc);
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifdef CIMPLE_OPENWBEM_MODULE
  CIMPLE_OPENWBEM_PROVIDER(/home/kschopmeyer/cimplework/pegasus/LINUX_X86_64_GNU/bin/genmod_Module);
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifdef CIMPLE_WMI_MODULE
# include "guid.h"
  CIMPLE_WMI_PROVIDER_ENTRY_POINTS(CLSID_/home/kschopmeyer/cimplework/pegasus/LINUX_X86_64_GNU/bin/genmod_Module)
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifndef __CIMPLE_FOUND_ENTRY_POINT
# error "No provider entry point found. Please define one of the following: CIMPLE_PEGASUS_MODULE, CIMPLE_CMPI_MODULE, CIMPLE_OPENWBEM_MODULE, CIMPLE_WMI_MODULE"
#endif
