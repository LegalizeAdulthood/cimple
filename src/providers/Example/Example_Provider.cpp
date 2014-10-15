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
    const Example* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Example_Provider::delete_instance(
    const Example* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Example_Provider::modify_instance(
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

int Example_Provider::proc(
    const Registration* registration,
    int operation, 
    void* arg0, 
    void* arg1, 
    void* arg2, 
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef Example Class;
    typedef Example_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
	    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo0") == 0)
    {
        typedef Example_foo0_method Method;
        Method* method = (Method*)arg2;
        return provider->foo0(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "foo1") == 0)
    {
        typedef Example_foo1_method Method;
        Method* method = (Method*)arg2;
        return provider->foo1(
            self,
            method->x,
            method->y,
            method->z,
            method->return_value);
    }
    if (strcasecmp(meth_name, "foo2") == 0)
    {
        typedef Example_foo2_method Method;
        Method* method = (Method*)arg2;
        return provider->foo2(
            self,
            method->w,
            method->x,
            method->y,
            method->z,
            method->return_value);
    }
    if (strcasecmp(meth_name, "foo3") == 0)
    {
        typedef Example_foo3_method Method;
        Method* method = (Method*)arg2;
        return provider->foo3(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "foo4") == 0)
    {
        typedef Example_foo4_method Method;
        Method* method = (Method*)arg2;
        return provider->foo4(
            self,
            method->x,
            method->return_value);
    }
    if (strcasecmp(meth_name, "foo5") == 0)
    {
        typedef Example_foo5_method Method;
        Method* method = (Method*)arg2;
        return provider->foo5(
            self,
            method->house,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
