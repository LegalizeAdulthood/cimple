// Generated by genprov 1.2.4
#include "CIMPLE_Widget_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CIMPLE_Widget_Provider::CIMPLE_Widget_Provider()
{
}

CIMPLE_Widget_Provider::~CIMPLE_Widget_Provider()
{
}

Load_Status CIMPLE_Widget_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CIMPLE_Widget_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CIMPLE_Widget_Provider::get_instance(
    const CIMPLE_Widget* model,
    CIMPLE_Widget*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CIMPLE_Widget_Provider::enum_instances(
    const CIMPLE_Widget* model,
    Enum_Instances_Handler<CIMPLE_Widget>* handler)
{
    CIMPLE_Widget* inst = CIMPLE_Widget::create();

    inst->Key.set(1234);
    inst->Color.set("Cyan");
    inst->Flag.set(false);

    handler->handle(inst);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CIMPLE_Widget_Provider::create_instance(
    CIMPLE_Widget* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CIMPLE_Widget_Provider::delete_instance(
    const CIMPLE_Widget* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CIMPLE_Widget_Provider::modify_instance(
    const CIMPLE_Widget* model,
    const CIMPLE_Widget* instance)
{
    printf("**** modify_instance()\n");

    print(model);
    print(instance);

    return MODIFY_INSTANCE_OK;
}

/*@END@*/

CIMPLE_NAMESPACE_END
