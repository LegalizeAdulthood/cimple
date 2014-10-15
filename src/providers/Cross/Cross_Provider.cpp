#include "Cross_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Cross_Provider::Cross_Provider()
{
}

Cross_Provider::~Cross_Provider()
{
}

Load_Status Cross_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Cross_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Cross_Provider::get_instance(
    const Cross* model,
    Cross*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Cross_Provider::enum_instances(
    const Cross* model,
    Enum_Instances_Handler<Cross>* handler)
{
    Cross* cross = Cross::create();

    cross->left = Left::create();
    cross->left->__name_space = "Left";
    cross->left->key.value = 100;

    cross->right = Right::create();
    cross->right->__name_space = "Right";
    cross->right->key.value = 100;

    handler->handle(cross);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Cross_Provider::create_instance(
    Cross* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Cross_Provider::delete_instance(
    const Cross* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Cross_Provider::modify_instance(
    const Cross* model,
    const Cross* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status Cross_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status Cross_Provider::enum_references(
    const Instance* instance,
    const Cross* model,
    const String& role,
    Enum_References_Handler<Cross>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status Cross_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
printf("***** enum_associators()\n");

    // Left:
    {
        Left* left = cast<Left*>(instance);

        if (left && left->key.value == 100)
        {
            Right* right = Right::create();
            right->__name_space = "Right";
            right->key.set(100);
            handler->handle(right);

            return ENUM_ASSOCIATORS_OK;
        }
    }

    // Right:
    {
        Right* right = cast<Right*>(instance);

        if (right && right->key.value == 100)
        {
            Left* left = Left::create();
            left->__name_space = "Right";
            left->key.set(100);
            handler->handle(left);

            return ENUM_ASSOCIATORS_OK;
        }
    }

    return ENUM_ASSOCIATORS_FAILED;
    // return ENUM_ASSOCIATORS_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

