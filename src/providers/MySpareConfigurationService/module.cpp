//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENMOD.
//
//==============================================================================

#include <cimple/cimple.h>
#include "MySpareConfigurationService_Provider.h"

using namespace cimple;

static int __cimple_MySpareConfigurationService_Provider_proc(
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
    typedef MySpareConfigurationService Class;
    typedef MySpareConfigurationService_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Instance_Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "RequestStateChange") == 0)
    {
        typedef MySpareConfigurationService_RequestStateChange_method Method;
        Method* method = (Method*)arg2;
        return provider->RequestStateChange(
            self,
            method->RequestedState,
            method->Job,
            method->TimeoutPeriod,
            method->return_value);
    }

    if (strcasecmp(meth_name, "StartService") == 0)
    {
        typedef MySpareConfigurationService_StartService_method Method;
        Method* method = (Method*)arg2;
        return provider->StartService(
            self,
            method->return_value);
    }

    if (strcasecmp(meth_name, "StopService") == 0)
    {
        typedef MySpareConfigurationService_StopService_method Method;
        Method* method = (Method*)arg2;
        return provider->StopService(
            self,
            method->return_value);
    }

    if (strcasecmp(meth_name, "AssignSpares") == 0)
    {
        typedef MySpareConfigurationService_AssignSpares_method Method;
        Method* method = (Method*)arg2;
        return provider->AssignSpares(
            self,
            method->Job,
            method->InPool,
            method->InExtents,
            method->RedundancySet,
            method->return_value);
    }

    if (strcasecmp(meth_name, "UnassignSpares") == 0)
    {
        typedef MySpareConfigurationService_UnassignSpares_method Method;
        Method* method = (Method*)arg2;
        return provider->UnassignSpares(
            self,
            method->Job,
            method->InPool,
            method->InExtents,
            method->return_value);
    }

    if (strcasecmp(meth_name, "RebuildStorageExtent") == 0)
    {
        typedef MySpareConfigurationService_RebuildStorageExtent_method Method;
        Method* method = (Method*)arg2;
        return provider->RebuildStorageExtent(
            self,
            method->Job,
            method->Target,
            method->return_value);
    }

    if (strcasecmp(meth_name, "CheckParityConsistency") == 0)
    {
        typedef MySpareConfigurationService_CheckParityConsistency_method Method;
        Method* method = (Method*)arg2;
        return provider->CheckParityConsistency(
            self,
            method->Job,
            method->Target,
            method->return_value);
    }

    if (strcasecmp(meth_name, "RepairParity") == 0)
    {
        typedef MySpareConfigurationService_RepairParity_method Method;
        Method* method = (Method*)arg2;
        return provider->RepairParity(
            self,
            method->Job,
            method->Target,
            method->return_value);
    }

    return -1;
}

CIMPLE_MODULE(MySpareConfigurationService_Module);
CIMPLE_INSTANCE_PROVIDER(MySpareConfigurationService_Provider);

#ifdef CIMPLE_PEGASUS_MODULE
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

#ifdef CIMPLE_CMPI_MODULE
  CIMPLE_CMPI_INSTANCE_PROVIDER(MySpareConfigurationService_Provider);
#endif

#ifdef CIMPLE_OPENWBEM_MODULE
  CIMPLE_OPENWBEM_PROVIDER(MySpareConfigurationService_Module);
#endif
