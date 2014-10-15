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

Timer_Status Fan_Provider::timer(uint64& timeout_msec)
{
    return TIMER_RESCHEDULE;
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
    const Fan* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Fan_Provider::delete_instance(
    const Fan* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Fan_Provider::modify_instance(
    const Fan* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Fan_Provider::SetSpeed(
    const Fan* self,
    const Property<uint64>& DesiredSpeed,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int Fan_Provider::proc(
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

    typedef Fan Class;
    typedef Fan_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(
	    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "SetSpeed") == 0)
    {
        typedef Fan_SetSpeed_method Method;
        Method* method = (Method*)arg2;
        return provider->SetSpeed(
            self,
            method->DesiredSpeed,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
