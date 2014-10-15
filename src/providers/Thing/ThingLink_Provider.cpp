#include "ThingLink_Provider.h"

CIMPLE_NAMESPACE_BEGIN

ThingLink_Provider::ThingLink_Provider()
{
printf("ThingLink_Provider::ThingLink_Provider()\n");
}

ThingLink_Provider::~ThingLink_Provider()
{
printf("ThingLink_Provider::~ThingLink_Provider()\n");
}

Load_Status ThingLink_Provider::load()
{
printf("ThingLink_Provider::load()\n");
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
printf("ThingLink_Provider::unload()\n");
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

int ThingLink_Provider::proc(
    const Registration* registration,
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

    typedef ThingLink Class;
    typedef ThingLink_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
