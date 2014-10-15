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
    const SNIA_SpareConfigurationService* model,
    const SNIA_SpareConfigurationService* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::RequestStateChange(
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

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::RebuildStorageExtent(
    const SNIA_SpareConfigurationService* self,
    CIM_ConcreteJob*& Job,
    const CIM_StorageExtent* Target,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status SNIA_SpareConfigurationService_Provider::CheckParityConsistency(
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

/*@END@*/

CIMPLE_NAMESPACE_END

