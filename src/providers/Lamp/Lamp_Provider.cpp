#include "Lamp_Provider.h"

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

    return LOAD_OK;
}

Unload_Status Lamp_Provider::unload()
{
    TRACE;
    return UNLOAD_OK;
}

Timer_Status Lamp_Provider::timer(uint64& timeout_msec)
{
    TRACE;
    return TIMER_CANCEL;
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
    const Lamp* instance)
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
    const Lamp* instance)
{
    TRACE;
    return _map.modify_instance(instance);
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

int Lamp_Provider::proc(
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
    TRACE;

    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef Lamp Class;
    typedef Lamp_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
	    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo") == 0)
    {
        typedef Lamp_foo_method Method;
        Method* method = (Method*)arg2;
        return provider->foo(
            self,
            method->arg1,
            method->arg2,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
