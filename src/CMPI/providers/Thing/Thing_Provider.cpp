#include "Thing_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Thing_Provider::Thing_Provider()
{
}

Thing_Provider::~Thing_Provider()
{
}

Load_Status Thing_Provider::load()
{
    Thing* thing;
    
    thing = Thing::create();
    thing->key.value = 100;
    _map.insert(thing);

    thing = Thing::create();
    thing->key.value = 200;
    _map.insert(thing);

    return LOAD_OK;
}

Unload_Status Thing_Provider::unload()
{
    return UNLOAD_OK;
}

Timer_Status Thing_Provider::timer(uint64& timeout_msec)
{
    return TIMER_CANCEL;
}

Get_Instance_Status Thing_Provider::get_instance(
    const Thing* model,
    Thing*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Thing_Provider::enum_instances(
    const Thing* model,
    Enum_Instances_Handler<Thing>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
	handler->handle(_map[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Thing_Provider::create_instance(
    const Thing* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Thing_Provider::delete_instance(
    const Thing* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Thing_Provider::modify_instance(
    const Thing* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Thing_Provider::proc(
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

    typedef Thing Class;
    typedef Thing_Provider Provider;
    return Provider_Proc_T<Provider>::proc(
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
