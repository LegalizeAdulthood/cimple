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
    MySpareConfigurationService* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status MySpareConfigurationService_Provider::delete_instance(
    const MySpareConfigurationService* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status MySpareConfigurationService_Provider::modify_instance(
    const MySpareConfigurationService* model,
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

Invoke_Method_Status MySpareConfigurationService_Provider::CheckParityConsistency(
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

/*@END@*/

CIMPLE_NAMESPACE_END
