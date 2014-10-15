// Generated by genprov 2.0.5
#include "CrossSubClass_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CrossSubClass_Provider::CrossSubClass_Provider()
{
}

CrossSubClass_Provider::~CrossSubClass_Provider()
{
}

Load_Status CrossSubClass_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CrossSubClass_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CrossSubClass_Provider::get_instance(
    const CrossSubClass* model,
    CrossSubClass*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CrossSubClass_Provider::enum_instances(
    const CrossSubClass* model,
    Enum_Instances_Handler<CrossSubClass>* handler)
{
    // Enumerate the single instance of the association
    {
        CrossSubClass* crosssubclass = CrossSubClass::create();
        crosssubclass->left = Left::create();
        crosssubclass->left->__name_space = "root/PG_Interop";
        crosssubclass->left->key.value = 3;
    
        crosssubclass->right = Right::create();
        crosssubclass->right->__name_space = "root/cimv2";
        crosssubclass->right->key.value = 3;

        crosssubclass->addedProperty.value = "Worthless string";
    
        handler->handle(crosssubclass);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CrossSubClass_Provider::create_instance(
    CrossSubClass* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CrossSubClass_Provider::delete_instance(
    const CrossSubClass* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CrossSubClass_Provider::modify_instance(
    const CrossSubClass* model,
    const CrossSubClass* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status CrossSubClass_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_Associators_Status CrossSubClass_Provider::enum_associators(
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

        if (left && left->key.value == 3)
        {
            Right* right = Right::create();
            right->__name_space = "root/cimv2";
            right->key.set(3);
            handler->handle(right);

            return ENUM_ASSOCIATORS_OK;
        }
    }

    // Right:
    {
        Right* right = cast<Right*>(instance);

        if (right && right->key.value == 3)
        {
            Left* left = Left::create();
            left->__name_space = "root/PG_Interop";
            left->key.set(3);
            handler->handle(left);

            return ENUM_ASSOCIATORS_OK;
        }
    }

    return ENUM_ASSOCIATORS_UNSUPPORTED;
}

Enum_References_Status CrossSubClass_Provider::enum_references(
    const Instance* instance,
    const CrossSubClass* model,
    const String& role,
    Enum_References_Handler<CrossSubClass>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END
