#include "LampLink_Provider.h"
#include "Lamp.h"

#if 0
# define CIMPLE_TRACE
#else
# define TRACE
#endif

CIMPLE_NAMESPACE_BEGIN

LampLink_Provider::LampLink_Provider()
{
    TRACE;
}

LampLink_Provider::~LampLink_Provider()
{
    TRACE;
}

Load_Status LampLink_Provider::load()
{
    TRACE;
    return LOAD_OK;
}

Unload_Status LampLink_Provider::unload()
{
    TRACE;
    return UNLOAD_OK;
}

Timer_Status LampLink_Provider::timer(uint64& timeout_msec)
{
    TRACE;
    return TIMER_CANCEL;
}

Get_Instance_Status LampLink_Provider::get_instance(
    const LampLink* model,
    LampLink*& instance)
{
    TRACE;
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status LampLink_Provider::enum_instances(
    const LampLink* model,
    Enum_Instances_Handler<LampLink>* handler)
{
    TRACE;
    LampLink* link;

    link = LampLink::create();
    link->left = Lamp::create();
    nullify_non_keys(link->left);
    link->left->model.value = "A";
    link->right = Lamp::create();
    nullify_non_keys(link->right);
    link->right->model.value = "B";
    handler->handle(link);

    link = LampLink::create();
    link->left = Lamp::create();
    nullify_non_keys(link->left);
    link->left->model.value = "B";
    link->right = Lamp::create();
    nullify_non_keys(link->right);
    link->right->model.value = "A";
    handler->handle(link);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status LampLink_Provider::create_instance(
    const LampLink* instance)
{
    TRACE;
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status LampLink_Provider::delete_instance(
    const LampLink* instance)
{
    TRACE;
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status LampLink_Provider::modify_instance(
    const LampLink* instance)
{
    TRACE;
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status LampLink_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    TRACE;
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status LampLink_Provider::enum_references(
    const Instance* instance,
    const LampLink* model,
    const String& role,
    Enum_References_Handler<LampLink>* handler)
{
    TRACE;
    return ENUM_REFERENCES_UNSUPPORTED;
}

int LampLink_Provider::proc(
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
    TRACE;

    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef LampLink Class;
    typedef LampLink_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration, 
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
