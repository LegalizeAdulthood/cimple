#include "ModernLamp_Provider.h"

CIMPLE_NAMESPACE_BEGIN

ModernLamp_Provider::ModernLamp_Provider()
{
}

ModernLamp_Provider::~ModernLamp_Provider()
{
}

Load_Status ModernLamp_Provider::load()
{
    return LOAD_OK;
}

Unload_Status ModernLamp_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status ModernLamp_Provider::get_instance(
    const ModernLamp* model,
    ModernLamp*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status ModernLamp_Provider::enum_instances(
    const ModernLamp* model,
    Enum_Instances_Handler<ModernLamp>* handler)
{
    ModernLamp* inst = ModernLamp::create();
    inst->model.value = "Zippy";
    inst->vendor.value = "Euro Lamps Inc";
    inst->wattage.value = 5000;
    inst->color.value = "White";
    inst->artist.value = "Jean Do Van Dam";

    handler->handle(inst);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status ModernLamp_Provider::create_instance(
    const ModernLamp* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status ModernLamp_Provider::delete_instance(
    const ModernLamp* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status ModernLamp_Provider::modify_instance(
    const ModernLamp* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status ModernLamp_Provider::foo(
    const ModernLamp* self,
    const Property<String>& arg1,
    const Property<String>& arg2,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

