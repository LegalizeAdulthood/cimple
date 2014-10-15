#include "SNIA_SpareConfigurationService_Provider.h"

CIMPLE_NAMESPACE_BEGIN

SNIA_SpareConfigurationService_Provider::
    SNIA_SpareConfigurationService_Provider()
{
}

SNIA_SpareConfigurationService_Provider::
    ~SNIA_SpareConfigurationService_Provider()
{
}

Load_Status SNIA_SpareConfigurationService_Provider::load()
{
    return LOAD_OK;
}

Unload_Status SNIA_SpareConfigurationService_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status SNIA_SpareConfigurationService_Provider::get_instance(
    const SNIA_SpareConfigurationService* model,
    SNIA_SpareConfigurationService*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status SNIA_SpareConfigurationService_Provider::enum_instances(
    const SNIA_SpareConfigurationService* model,
    Enum_Instances_Handler<SNIA_SpareConfigurationService>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status SNIA_SpareConfigurationService_Provider::create_instance(
    const SNIA_SpareConfigurationService* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status SNIA_SpareConfigurationService_Provider::delete_instance(
    const SNIA_SpareConfigurationService* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status SNIA_SpareConfigurationService_Provider::modify_instance(
    const SNIA_SpareConfigurationService* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::
RequestStateChange(
    const SNIA_SpareConfigurationService* self,
    const Property<uint16>& RequestedState,
    CIM_ConcreteJob*& Job,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::StartService(
    const SNIA_SpareConfigurationService* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::StopService(
    const SNIA_SpareConfigurationService* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::AssignSpares(
    const SNIA_SpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StoragePool* InPool,
    const Array<CIM_StorageExtent*>& InExtents,
    const CIM_StorageRedundancySet* RedundancySet,
    Property<uint32>& return_value)
{
    printf("===== SNIA_SpareConfigurationService_Provider::AssignSpares()\n");

    if (InPool)
        print(InPool, true);

    for (size_t i = 0; i < InExtents.size(); i++)
    {
        CIM_StorageExtent* ext = InExtents[i];

        if (ext)
            print(ext, true);
        else
            return INVOKE_METHOD_FAILED;
    }

    Job = CIM_ConcreteJob::create();
    Job->InstanceID.value = "1000";

    return_value.value = 100;
    return_value.null = false;

    return INVOKE_METHOD_OK;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::UnassignSpares(
    const SNIA_SpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StoragePool* InPool,
    const Array<CIM_StorageExtent*>& InExtents,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::
RebuildStorageExtent(
    const SNIA_SpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::
CheckParityConsistency(
    const SNIA_SpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::RepairParity(
    const SNIA_SpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int SNIA_SpareConfigurationService_Provider::proc(
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
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef SNIA_SpareConfigurationService Class;
    typedef SNIA_SpareConfigurationService_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "RequestStateChange") == 0)
    {
        typedef SNIA_SpareConfigurationService_RequestStateChange_method Method;
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
        typedef SNIA_SpareConfigurationService_StartService_method Method;
        Method* method = (Method*)arg2;
        return provider->StartService(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "StopService") == 0)
    {
        typedef SNIA_SpareConfigurationService_StopService_method Method;
        Method* method = (Method*)arg2;
        return provider->StopService(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "AssignSpares") == 0)
    {
        typedef SNIA_SpareConfigurationService_AssignSpares_method Method;
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
        typedef SNIA_SpareConfigurationService_UnassignSpares_method Method;
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
        typedef SNIA_SpareConfigurationService_RebuildStorageExtent_method 
            Method;
        Method* method = (Method*)arg2;
        return provider->RebuildStorageExtent(
            self,
            method->Job,
            method->Target,
            method->return_value);
    }
    if (strcasecmp(meth_name, "CheckParityConsistency") == 0)
    {
        typedef SNIA_SpareConfigurationService_CheckParityConsistency_method 
            Method;
        Method* method = (Method*)arg2;
        return provider->CheckParityConsistency(
            self,
            method->Job,
            method->Target,
            method->return_value);
    }
    if (strcasecmp(meth_name, "RepairParity") == 0)
    {
        typedef SNIA_SpareConfigurationService_RepairParity_method Method;
        Method* method = (Method*)arg2;
        return provider->RepairParity(
            self,
            method->Job,
            method->Target,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/SNIA_SpareConfigurationService/SNIA_SpareConfigurationService_Provider.cpp,v 1.3 2007/03/07 20:25:28 mbrasher-public Exp $");
