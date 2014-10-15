#include "MySpareConfigurationService_Provider.h"

CIMPLE_NAMESPACE_BEGIN

MySpareConfigurationService_Provider::MySpareConfigurationService_Provider()
{
}

MySpareConfigurationService_Provider::~MySpareConfigurationService_Provider()
{
}

Load_Status MySpareConfigurationService_Provider::load()
{
    return LOAD_OK;
}

Unload_Status MySpareConfigurationService_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status MySpareConfigurationService_Provider::get_instance(
    const MySpareConfigurationService* model,
    MySpareConfigurationService*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status MySpareConfigurationService_Provider::enum_instances(
    const MySpareConfigurationService* model,
    Enum_Instances_Handler<MySpareConfigurationService>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status MySpareConfigurationService_Provider::create_instance(
    const MySpareConfigurationService* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status MySpareConfigurationService_Provider::delete_instance(
    const MySpareConfigurationService* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status MySpareConfigurationService_Provider::modify_instance(
    const MySpareConfigurationService* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::RequestStateChange(
    const MySpareConfigurationService* self,
    const Property<uint16>& RequestedState,
    CIM_ConcreteJob*& Job,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::StartService(
    const MySpareConfigurationService* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::StopService(
    const MySpareConfigurationService* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::AssignSpares(
    const MySpareConfigurationService* self,
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

Invoke_Method_Status MySpareConfigurationService_Provider::UnassignSpares(
    const MySpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StoragePool* InPool,
    const Array<CIM_StorageExtent*>& InExtents,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::RebuildStorageExtent(
    const MySpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::
CheckParityConsistency(
    const MySpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status MySpareConfigurationService_Provider::RepairParity(
    const MySpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int MySpareConfigurationService_Provider::proc(
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

    typedef MySpareConfigurationService Class;
    typedef MySpareConfigurationService_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
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
        typedef 
        MySpareConfigurationService_CheckParityConsistency_method Method;
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

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MySpareConfigurationService/MySpareConfigurationService_Provider.cpp,v 1.2 2007/03/07 20:25:26 mbrasher-public Exp $");

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MySpareConfigurationService/MySpareConfigurationService_Provider.cpp,v 1.2 2007/03/07 20:25:26 mbrasher-public Exp $");
