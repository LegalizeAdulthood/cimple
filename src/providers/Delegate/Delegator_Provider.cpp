#include "Delegator_Provider.h"
#include "Delegate.h"

CIMPLE_NAMESPACE_BEGIN

Delegator_Provider::Delegator_Provider()
{
}

Delegator_Provider::~Delegator_Provider()
{
}

Load_Status Delegator_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Delegator_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Delegator_Provider::get_instance(
    const Delegator* model,
    Delegator*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Delegator_Provider::enum_instances(
    const Delegator* model,
    Enum_Instances_Handler<Delegator>* handler)
{
    Delegate* delegate = Delegate::create();

    Instance_Enumerator e;
    
    if (cimom::enum_instances( "root/cimv2", delegate, e) != 0)
    {
        return ENUM_INSTANCES_FAILED;
    }

    for (; e; e++)
    {
        Ref<Instance> r = e();

        Delegate* delegate = cast<Delegate*>(r.ptr());

        if (delegate)
        {
            Delegator* delegator = Delegator::create();
            delegator->key = delegate->key;
            delegator->message = delegate->message;
            handler->handle(delegator);
        }
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Delegator_Provider::create_instance(
    Delegator* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Delegator_Provider::delete_instance(
    const Delegator* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Delegator_Provider::modify_instance(
    const Delegator* model,
    const Delegator* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END
