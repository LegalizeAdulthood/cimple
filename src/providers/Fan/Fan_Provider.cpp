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
    Fan* fan = _map.lookup(model);

    if (fan)
    {
        instance = fan->clone();
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Fan_Provider::enum_instances(
    const Fan* model,
    Enum_Instances_Handler<Fan>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
    {
        Fan* instance = _map[i]->clone();
        handler->handle(instance);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Fan_Provider::create_instance(
    Fan* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Fan_Provider::delete_instance(
    const Fan* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Fan_Provider::modify_instance(
    const Fan* model,
    const Fan* instance)
{
    Fan* fan = _map.lookup(instance);

    if (fan)
    {
        copy(fan, instance);
        return MODIFY_INSTANCE_OK;
    }

    return MODIFY_INSTANCE_NOT_FOUND;
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

