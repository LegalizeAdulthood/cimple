//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENMOD 1.0.21
//
//==============================================================================

#include <cimple/cimple.h>
#include "EA_Class2_Provider.h"

using namespace cimple;

static int __cimple_EA_Class2_Provider_proc(
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
    typedef EA_Class2 Class;
    typedef EA_Class2_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Instance_Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo1") == 0)
    {
        typedef EA_Class2_foo1_method Method;
        Method* method = (Method*)arg2;
        return provider->foo1(
            self,
            method->return_value);
    }

    if (strcasecmp(meth_name, "foo2") == 0)
    {
        typedef EA_Class2_foo2_method Method;
        Method* method = (Method*)arg2;
        return provider->foo2(
            self,
            method->return_value);
    }

    if (strcasecmp(meth_name, "foo3") == 0)
    {
        typedef EA_Class2_foo3_method Method;
        Method* method = (Method*)arg2;
        return provider->foo3(
            self,
            method->arg1,
            method->arg2,
            method->return_value);
    }

    if (strcasecmp(meth_name, "foo4") == 0)
    {
        typedef EA_Class2_foo4_method Method;
        Method* method = (Method*)arg2;
        return provider->foo4(
            self,
            method->arg1,
            method->arg2,
            method->return_value);
    }

    return -1;
}

CIMPLE_MODULE(EA_Module);
CIMPLE_INSTANCE_PROVIDER(EA_Class2_Provider);

#ifdef CIMPLE_PEGASUS_MODULE
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifdef CIMPLE_CMPI_MODULE
  CIMPLE_CMPI_INSTANCE_PROVIDER(EA_Class2_Provider);
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifdef CIMPLE_OPENWBEM_MODULE
  CIMPLE_OPENWBEM_PROVIDER(EA_Module);
# define __CIMPLE_FOUND_ENTRY_POINT
#endif

#ifndef __CIMPLE_FOUND_ENTRY_POINT
# error "No provider entry point found. Please define one of the following: CIMPLE_PEGASUS_MODULE, CIMPLE_CMPI_MODULE, CIMPLE_OPENWBEM_MODULE"
#endif
