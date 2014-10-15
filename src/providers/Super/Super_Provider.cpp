#include "Super_Provider.h"
#include "Sub1.h"
#include "Sub2.h"

CIMPLE_NAMESPACE_BEGIN

Super_Provider::Super_Provider()
{
}

Super_Provider::~Super_Provider()
{
}

Load_Status Super_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Super_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Super_Provider::get_instance(
    const Super* model,
    Super*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Super_Provider::enum_instances(
    const Super* model,
    Enum_Instances_Handler<Super>* handler)
{
    if (eqi(model->meta_class->name, "Sub1"))
    {
        Sub1* sub1 = Sub1::create();
        sub1->key.value = 1;
        sub1->sub1.value = 111;
        handler->handle(cast<Super*>(sub1));
    }

    if (eqi(model->meta_class->name, "Sub2"))
    {
        Sub2* sub2 = Sub2::create();
        sub2->key.value = 2;
        sub2->sub2.value = 222;
        handler->handle(cast<Super*>(sub2));
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Super_Provider::create_instance(
    Super* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Super_Provider::delete_instance(
    const Super* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Super_Provider::modify_instance(
    const Super* model,
    const Super* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

