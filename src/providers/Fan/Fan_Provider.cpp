#include "Fan_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Fan_Provider::Fan_Provider()
{
}

Fan_Provider::~Fan_Provider()
{
}

Load_Status Fan_Provider::load()
{
    // Create three instances and add them to the map.

    Fan* instance = Fan::create();
    instance->DeviceID.value = "FAN01";
    instance->Speed.value = 1000;
    instance->DesiredSpeed.value = 1000;
    _map.insert(instance);

    instance = Fan::create();
    instance->DeviceID.value = "FAN02";
    instance->Speed.value = 2000;
    instance->DesiredSpeed.value = 2000;
    _map.insert(instance);

    instance = Fan::create();
    instance->DeviceID.value = "FAN03";
    instance->Speed.value = 3000;
    instance->DesiredSpeed.value = 3000;
    _map.insert(instance);

    return LOAD_OK;
}

Unload_Status Fan_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Fan_Provider::get_instance(
    const Fan* model,
    Fan*& instance)
{
    // This is more efficient than using NOT_SUPPORTED
    return _map.get_instance(model, instance);
}

Enum_Instances_Status Fan_Provider::enum_instances(
    const Fan* model,
    Enum_Instances_Handler<Fan>* handler)
{
    return _map.enum_instances(model, handler);
}

Create_Instance_Status Fan_Provider::create_instance(
    Fan* instance)
{
    return _map.create_instance(instance);}

Delete_Instance_Status Fan_Provider::delete_instance(
    const Fan* instance)
{
    return _map.delete_instance(instance);}

Modify_Instance_Status Fan_Provider::modify_instance(
    const Fan* model,
    const Fan* instance)
{
    return _map.modify_instance(model, instance);

}

Invoke_Method_Status Fan_Provider::SetSpeed(
    const Fan* self,
    const Property<uint64>& DesiredSpeed,
    Property<uint32>& return_value)
{
    return_value.null = false;
    return_value.value = 1000;
    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END

