#include "CIM_DiskDrive_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CIM_DiskDrive_Provider::CIM_DiskDrive_Provider()
{
}

CIM_DiskDrive_Provider::~CIM_DiskDrive_Provider()
{
}

Load_Status CIM_DiskDrive_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CIM_DiskDrive_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CIM_DiskDrive_Provider::get_instance(
    const CIM_DiskDrive* model,
    CIM_DiskDrive*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CIM_DiskDrive_Provider::enum_instances(
    const CIM_DiskDrive* model,
    Enum_Instances_Handler<CIM_DiskDrive>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CIM_DiskDrive_Provider::create_instance(
    CIM_DiskDrive* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CIM_DiskDrive_Provider::delete_instance(
    const CIM_DiskDrive* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CIM_DiskDrive_Provider::modify_instance(
    const CIM_DiskDrive* model,
    const CIM_DiskDrive* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::RequestStateChange(
    const CIM_DiskDrive* self,
    const Property<uint16>& RequestedState,
    CIM_ConcreteJob*& Job,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::SetPowerState(
    const CIM_DiskDrive* self,
    const Property<uint16>& PowerState,
    const Property<Datetime>& Time,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::Reset(
    const CIM_DiskDrive* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::EnableDevice(
    const CIM_DiskDrive* self,
    const Property<boolean>& Enabled,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::OnlineDevice(
    const CIM_DiskDrive* self,
    const Property<boolean>& Online,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::QuiesceDevice(
    const CIM_DiskDrive* self,
    const Property<boolean>& Quiesce,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::SaveProperties(
    const CIM_DiskDrive* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::RestoreProperties(
    const CIM_DiskDrive* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::LockMedia(
    const CIM_DiskDrive* self,
    const Property<boolean>& Lock,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

