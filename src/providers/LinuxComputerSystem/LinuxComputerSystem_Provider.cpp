#include "LinuxComputerSystem_Provider.h"

CIMPLE_NAMESPACE_BEGIN

LinuxComputerSystem_Provider::LinuxComputerSystem_Provider()
{
}

LinuxComputerSystem_Provider::~LinuxComputerSystem_Provider()
{
}

Load_Status LinuxComputerSystem_Provider::load()
{
    return LOAD_OK;
}

Unload_Status LinuxComputerSystem_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status LinuxComputerSystem_Provider::get_instance(
    const LinuxComputerSystem* model,
    LinuxComputerSystem*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status LinuxComputerSystem_Provider::enum_instances(
    const LinuxComputerSystem* model,
    Enum_Instances_Handler<LinuxComputerSystem>* handler)
{
    LinuxComputerSystem* inst = LinuxComputerSystem::create();
    inst->Name.value = "monday";
    inst->CreationClassName.value = "LinuxComputerSystem";
    handler->handle(inst);

    inst = LinuxComputerSystem::create();
    inst->Name.value = "tuesday";
    inst->CreationClassName.value = "LinuxComputerSystem";
    handler->handle(inst);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status LinuxComputerSystem_Provider::create_instance(
    LinuxComputerSystem* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status LinuxComputerSystem_Provider::delete_instance(
    const LinuxComputerSystem* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status LinuxComputerSystem_Provider::modify_instance(
    const LinuxComputerSystem* model,
    const LinuxComputerSystem* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status LinuxComputerSystem_Provider::RequestStateChange(
    const LinuxComputerSystem* self,
    const Property<uint16>& RequestedState,
    CIM_ConcreteJob*& Job,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status LinuxComputerSystem_Provider::SetPowerState(
    const LinuxComputerSystem* self,
    const Property<uint32>& PowerState,
    const Property<Datetime>& Time,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

