#include "Lamp_Provider.h"
#include "Persistent.h"
#include "ModernLamp.h"

CIMPLE_NAMESPACE_BEGIN

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

Lamp_Provider::Lamp_Provider()
{
    TRACE;
}

Lamp_Provider::~Lamp_Provider()
{
    TRACE;
}

Load_Status Lamp_Provider::load()
{
    TRACE;

    Lamp* instance;
    
    instance = Lamp::create();
    instance->model.value = "A";
    instance->vendor.value = "Euro Lamps Inc";
    instance->wattage.value = 300;
    instance->color.value = "Silver";
    _map.insert(instance);

    instance = Lamp::create();
    instance->model.value = "B";
    instance->vendor.value = "US Lighting";
    instance->wattage.value = 400;
    instance->color.value = "Blue";
    _map.insert(instance);

    {
        ModernLamp* inst = ModernLamp::create();
        inst->model.value = "Zippy";
        inst->vendor.value = "Euro Lamps Inc";
        inst->wattage.value = 5000;
        inst->color.value = "White";
        inst->artist.value = "Jean Do Van Dam";
        _map.insert(cast<Lamp*>(inst));
    }

    return LOAD_OK;
}

Unload_Status Lamp_Provider::unload()
{
    TRACE;
    return UNLOAD_OK;
}

Get_Instance_Status Lamp_Provider::get_instance(
    const Lamp* model,
    Lamp*& instance)
{
    TRACE;

    return _map.get_instance(model, instance);
}

Enum_Instances_Status Lamp_Provider::enum_instances(
    const Lamp* model,
    Enum_Instances_Handler<Lamp>* handler)
{
    TRACE;
    return _map.enum_instances(model, handler);
}

Create_Instance_Status Lamp_Provider::create_instance(
    Lamp* instance)
{
    TRACE;
    return _map.create_instance(instance);
}

Delete_Instance_Status Lamp_Provider::delete_instance(
    const Lamp* instance)
{
    TRACE;
    return _map.delete_instance(instance);
}

Modify_Instance_Status Lamp_Provider::modify_instance(
    const Lamp* model,
    const Lamp* instance)
{
    TRACE;
    return _map.modify_instance(model, instance);
}

Invoke_Method_Status Lamp_Provider::foo(
    const Lamp* self,
    const Property<String>& arg1,
    const Property<String>& arg2,
    Property<uint32>& return_value)
{
    TRACE;
    return_value.null = false;
    return_value.value = 100;

    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END

