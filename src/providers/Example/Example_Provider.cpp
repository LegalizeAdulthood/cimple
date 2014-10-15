#include "Example_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Example_Provider::Example_Provider()
{
}

Example_Provider::~Example_Provider()
{
}

Load_Status Example_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Example_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Example_Provider::get_instance(
    const Example* model,
    Example*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Example_Provider::enum_instances(
    const Example* model,
    Enum_Instances_Handler<Example>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Example_Provider::create_instance(
    Example* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Example_Provider::delete_instance(
    const Example* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Example_Provider::modify_instance(
    const Example* model,
    const Example* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Example_Provider::foo0(
    const Example* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Example_Provider::foo1(
    const Example* self,
    const Property<real32>& x,
    const Property<uint32>& y,
    const Property<boolean>& z,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Example_Provider::foo2(
    const Example* self,
    const Property<String>& w,
    const Property<real32>& x,
    const Property<uint32>& y,
    const Property<boolean>& z,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Example_Provider::foo3(
    const Example* self,
    Property<String>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Example_Provider::foo4(
    const Example* self,
    const Property<Array_real32>& x,
    Property<String>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Example_Provider::foo5(
    const Example* self,
    const House* house,
    Property<String>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

