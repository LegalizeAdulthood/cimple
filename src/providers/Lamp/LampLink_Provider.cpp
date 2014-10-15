#include "LampLink_Provider.h"
#include "Lamp.h"

#if 0
# define TRACE CIMPLE_TRACE
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
    LampLink* instance)
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
    const LampLink* model,
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

Enum_Associators_Status LampLink_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
    TRACE;

    // The source must always be "Lamp".

    Lamp* source = cast<Lamp*>(instance);

    if (!source)
        return ENUM_ASSOCIATORS_FAILED;

    // The result class must be "Lamp" too.

    if (result_class.size() && result_class != "Lamp")
        return ENUM_ASSOCIATORS_FAILED;

    // Handle the "left" to "right" role.

    if ((eqi(role, "left") || role.empty()) &&
        (eqi(result_role, "right") || result_role.empty()))
    {
        if (source->model.value == "A")
        {
            Lamp* target = Lamp::create(true);
            target->model.set("B");
            target->vendor.set("US Lighting");
            target->wattage.set(400);
            target->color.set("Blue");
            handler->handle(target);
        }

        if (source->model.value == "B")
        {
            Lamp* target = Lamp::create(true);
            target->model.set("A");
            target->vendor.set("Euro Lamps Inc");
            target->wattage.set(300);
            target->color.set("Silver");
            handler->handle(target);
        }
    }

    // Handle the "right" to "left" role.

    if ((eqi(role, "right") || role.empty()) &&
        (eqi(result_role, "left") || result_role.empty()))
    {
        if (source->model.value == "A")
        {
            Lamp* target = Lamp::create(true);
            target->model.set("B");
            target->vendor.set("US Lighting");
            target->wattage.set(400);
            target->color.set("Blue");
            handler->handle(target);
        }

        if (source->model.value == "B")
        {
            Lamp* target = Lamp::create(true);
            target->model.set("A");
            target->vendor.set("Euro Lamps Inc");
            target->wattage.set(300);
            target->color.set("Silver");
            handler->handle(target);
        }
    }

    return ENUM_ASSOCIATORS_OK;
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

CIMPLE_NAMESPACE_END

