#include "Left_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Left_Provider::Left_Provider()
{
}

Left_Provider::~Left_Provider()
{
}

Load_Status Left_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Left_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Left_Provider::get_instance(
    const Left* model,
    Left*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Left_Provider::enum_instances(
    const Left* model,
    Enum_Instances_Handler<Left>* handler)
{
    {
        Left* left = Left::create();
        left->key.value = 1;
        handler->handle(left);
    }
    {
        Left* left = Left::create();
        left->key.value = 2;
        handler->handle(left);
    }
    {
        Left* left = Left::create();
        left->key.value = 3;
        handler->handle(left);
    }
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Left_Provider::create_instance(
    Left* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Left_Provider::delete_instance(
    const Left* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Left_Provider::modify_instance(
    const Left* model,
    const Left* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

