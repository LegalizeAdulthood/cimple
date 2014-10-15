#include "ThingLink_Provider.h"

CIMPLE_NAMESPACE_BEGIN

ThingLink_Provider::ThingLink_Provider()
{
}

ThingLink_Provider::~ThingLink_Provider()
{
}

Load_Status ThingLink_Provider::load()
{
    ThingLink* link;
    
    link = ThingLink::create();
    link->left = Thing::create();
    link->left->key.value = 100;
    link->right = Thing::create();
    link->right->key.value = 200;
    _map.insert(link);

    return LOAD_OK;
}

Unload_Status ThingLink_Provider::unload()
{
    return UNLOAD_OK;
}

Timer_Status ThingLink_Provider::timer(uint64& timeout_msec)
{
    return TIMER_CANCEL;
}

Get_Instance_Status ThingLink_Provider::get_instance(
    const ThingLink* model,
    ThingLink*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status ThingLink_Provider::enum_instances(
    const ThingLink* model,
    Enum_Instances_Handler<ThingLink>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
	handler->handle(_map[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status ThingLink_Provider::create_instance(
    const ThingLink* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status ThingLink_Provider::delete_instance(
    const ThingLink* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status ThingLink_Provider::modify_instance(
    const ThingLink* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int ThingLink_Provider::proc(
    int operation, void* arg0, void* arg1, void* arg2, void* arg3)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef ThingLink Class;
    typedef ThingLink_Provider Provider;
    return Provider_Proc_T<Provider>::proc(operation, arg0, arg1, arg2, arg3);
}

CIMPLE_NAMESPACE_END
