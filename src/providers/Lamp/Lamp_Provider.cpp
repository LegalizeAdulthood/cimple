#include "Lamp_Provider.h"
#include "Fan.h"

CIMPLE_NAMESPACE_BEGIN

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

static void _test_cimom_ops()
{
    Ref<Fan> fan(Fan::create());
    Instance_Enumerator e;

    printf("===== cimom::enum_instances()\n");
    
    if (cimom::enum_instances("root/cimv2", fan.ptr(), e) == 0)
    {
	for (; e; e++)
	    print(e().ptr());
    }

    printf("===== cimom::get_instance()\n");

    {
	Ref<Fan> keys(Fan::create());
	keys->DeviceID.value = "FAN01";
	Ref<Instance> inst = cimom::get_instance("root/cimv2", keys.ptr());
	print(inst.ptr());
    }

    printf("===== cimom::modify_instance()\n");

    {
	Ref<Fan> inst(Fan::create());

	inst->DeviceID.value = "FAN01";
	inst->Speed.value = 1111;
	inst->DesiredSpeed.value = 1111;
	int result = cimom::modify_instance("root/cimv2", inst.ptr());

	if (result != 0)
	    printf("failed\n");
    }

    printf("===== cimom::get_instance()\n");

    {
	Ref<Fan> keys(Fan::create());
	keys->DeviceID.value = "FAN01";
	Ref<Instance> inst = cimom::get_instance("root/cimv2", keys.ptr());
	print(inst.ptr());
    }

    printf("===== cimom::delete_instance()\n");

    {
	Ref<Fan> key(Fan::create());
	key->DesiredSpeed.value = 1111;
	int result = cimom::delete_instance("root/cimv2", key.ptr());

	if (result != 0)
	    printf("cimom::delete_instance() failed\n");
    }

    printf("===== cimom::get_instance()\n");

    {
	Ref<Fan> keys(Fan::create());
	keys->DeviceID.value = "FAN01";
	Ref<Instance> inst = cimom::get_instance("root/cimv2", keys.ptr());

	if (inst)
	    print(inst.ptr());
	else
	    printf("cimom::get_instance() failed\n");
    }
}

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
