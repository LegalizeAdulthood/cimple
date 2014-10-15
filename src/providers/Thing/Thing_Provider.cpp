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

Get_Instance_Status Thing_Provider::get_instance(
    const Thing* model,
    Thing*& instance)
{
print(model);
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
    Thing* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Thing_Provider::delete_instance(
    const Thing* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Thing_Provider::modify_instance(
    const Thing* model,
    const Thing* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

