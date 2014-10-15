#include "Thing_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Thing_Provider::Thing_Provider()
{
}

Thing_Provider::~Thing_Provider()
{
}

static Thing* _create(uint32 key)
{
    Thing* thing = Thing::create();
    thing->key.set(key);
    thing->p0.set("This is a String");
    thing->p1.set("This is a String");
    thing->p2.set("This is a String");
    thing->p3.set("This is a String");
    thing->p4.set("This is a String");
    thing->p5.set("This is a String");
    thing->p6.set("This is a String");
    thing->p7.set("This is a String");
    thing->p8.set("This is a String");
    thing->p9.set("This is a String");

    return thing;
}

Load_Status Thing_Provider::load()
{
    _map.insert(_create(100));
    _map.insert(_create(200));
    _map.insert(_create(300));
    _map.insert(_create(400));
    _map.insert(_create(500));
    _map.insert(_create(600));
    _map.insert(_create(700));
    _map.insert(_create(800));
    _map.insert(_create(900));
    _map.insert(_create(1000));

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

