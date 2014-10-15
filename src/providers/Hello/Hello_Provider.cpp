#include "Hello_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Hello_Provider::Hello_Provider()
{
}

Hello_Provider::~Hello_Provider()
{
}

Load_Status Hello_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Hello_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Hello_Provider::get_instance(
    const Hello* model,
    Hello*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Hello_Provider::enum_instances(
    const Hello* model,
    Enum_Instances_Handler<Hello>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Hello_Provider::create_instance(
    Hello* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Hello_Provider::delete_instance(
    const Hello* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Hello_Provider::modify_instance(
    const Hello* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END
