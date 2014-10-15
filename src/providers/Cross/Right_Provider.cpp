#include "Right_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Right_Provider::Right_Provider()
{
}

Right_Provider::~Right_Provider()
{
}

Load_Status Right_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Right_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Right_Provider::get_instance(
    const Right* model,
    Right*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Right_Provider::enum_instances(
    const Right* model,
    Enum_Instances_Handler<Right>* handler)
{
    {
        Right* right = Right::create();
        right->key.value = 1;
        handler->handle(right);
    }
    {
        Right* right = Right::create();
        right->key.value = 2;
        handler->handle(right);
    }
    {
        Right* right = Right::create();
        right->key.value = 3;
        handler->handle(right);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Right_Provider::create_instance(
    Right* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Right_Provider::delete_instance(
    const Right* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Right_Provider::modify_instance(
    const Right* model,
    const Right* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

