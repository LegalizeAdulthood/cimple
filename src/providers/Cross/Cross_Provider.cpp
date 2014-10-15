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

    // create single instance pointing from left namespace
    // to right namespace
    // TODO: Get namespaces from input parameters rather than
    // fixing them in the code.
    // 
    {
        Cross* cross = Cross::create();
        cross->left = Left::create();
        cross->left->__name_space = "root/PG_Interop";
        cross->left->key.value = 1;
    
        cross->right = Right::create();
        cross->right->__name_space = "root/cimv2";
        cross->right->key.value = 1;
    
        handler->handle(cross);
    }

    // This instance is not cross namespace
    {

        Cross* cross = Cross::create();
        cross->left = Left::create();
        cross->left->key.value = 2;
    
        cross->right = Right::create();
        cross->right->key.value = 2;
    
        handler->handle(cross);
    }

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
    return ENUM_ASSOCIATORS_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

