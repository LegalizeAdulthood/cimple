#include "CIM_ConcreteJob_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CIM_ConcreteJob_Provider::CIM_ConcreteJob_Provider()
{
}

CIM_ConcreteJob_Provider::~CIM_ConcreteJob_Provider()
{
}

Load_Status CIM_ConcreteJob_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CIM_ConcreteJob_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CIM_ConcreteJob_Provider::get_instance(
    const CIM_ConcreteJob* model,
    CIM_ConcreteJob*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CIM_ConcreteJob_Provider::enum_instances(
    const CIM_ConcreteJob* model,
    Enum_Instances_Handler<CIM_ConcreteJob>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CIM_ConcreteJob_Provider::create_instance(
    CIM_ConcreteJob* instance)
{
    instance->InstanceID.value = "2222";
    instance->InstanceID.null = false;

    // print(instance, true);

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status CIM_ConcreteJob_Provider::delete_instance(
    const CIM_ConcreteJob* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CIM_ConcreteJob_Provider::modify_instance(
    const CIM_ConcreteJob* model,
    const CIM_ConcreteJob* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status CIM_ConcreteJob_Provider::KillJob(
    const CIM_ConcreteJob* self,
    const Property<boolean>& DeleteOnKill,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_ConcreteJob_Provider::RequestStateChange(
    const CIM_ConcreteJob* self,
    const Property<uint16>& RequestedState,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END
