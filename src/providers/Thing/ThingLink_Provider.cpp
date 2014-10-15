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
    ThingLink* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status ThingLink_Provider::delete_instance(
    const ThingLink* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status ThingLink_Provider::modify_instance(
    const ThingLink* model,
    const ThingLink* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status ThingLink_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status ThingLink_Provider::enum_references(
    const Instance* instance,
    const ThingLink* model,
    const String& role,
    Enum_References_Handler<ThingLink>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status ThingLink_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATORS_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

