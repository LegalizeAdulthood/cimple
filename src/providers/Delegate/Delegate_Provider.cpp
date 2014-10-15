#include "Delegate_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Delegate_Provider::Delegate_Provider()
{
}

Delegate_Provider::~Delegate_Provider()
{
}

Load_Status Delegate_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Delegate_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Delegate_Provider::get_instance(
    const Delegate* model,
    Delegate*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Delegate_Provider::enum_instances(
    const Delegate* model,
    Enum_Instances_Handler<Delegate>* handler)
{
    {
        Delegate* inst = Delegate::create();
        inst->key.value = 1000;
        inst->message.value = "one thousand";
        handler->handle(inst);
    }

    {
        Delegate* inst = Delegate::create();
        inst->key.value = 2000;
        inst->message.value = "two thousand";
        handler->handle(inst);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Delegate_Provider::create_instance(
    Delegate* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Delegate_Provider::delete_instance(
    const Delegate* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Delegate_Provider::modify_instance(
    const Delegate* model,
    const Delegate* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END
