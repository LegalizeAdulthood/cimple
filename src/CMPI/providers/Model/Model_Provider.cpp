#include "Model_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Model_Provider::Model_Provider()
{
}

Model_Provider::~Model_Provider()
{
}

Load_Status Model_Provider::load()
{
    printf("=== Model_Provider::load()\n");
    return LOAD_OK;
}

Unload_Status Model_Provider::unload()
{
    return UNLOAD_OK;
}

Timer_Status Model_Provider::timer(uint64& timeout)
{
    return TIMER_CANCEL;
}

Get_Instance_Status Model_Provider::get_instance(
    const Model* model,
    Model*& instance)
{
    instance = model->clone();

    if (!instance->prop1.null)
        instance->prop1.value = "property 1";

    if (!instance->prop2.null)
        instance->prop2.value = "property 2";

    if (!instance->prop3.null)
        instance->prop3.value = "property 3";

    if (!instance->prop4.null)
        instance->prop4.value = "property 4";

    if (!instance->prop5.null)
        instance->prop5.value = "property 5";

    return GET_INSTANCE_OK;
}

Enum_Instances_Status Model_Provider::enum_instances(
    const Model* model,
    Enum_Instances_Handler<Model>* handler)
{
    Model* inst = Model::create();
    inst->k1.value = "100";
    inst->k2.value = 100;
    inst->k3.value = true;
    inst->prop1.value = "property 1 (100)";
    inst->prop2.value = "property 2 (100)";
    handler->handle(inst);

    inst = Model::create();
    inst->k1.value = "200";
    inst->k2.value = 200;
    inst->k3.value = true;
    inst->prop1.value = "property 1 (200)";
    inst->prop2.value = "property 2 (200)";
    handler->handle(inst);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Model_Provider::create_instance(
    const Model* instance)
{
    printf("=== Model_Provider::create_instance()\n");
    print(instance);

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status Model_Provider::delete_instance(
    const Model* instance)
{
    return DELETE_INSTANCE_OK;
}

Modify_Instance_Status Model_Provider::modify_instance(
    const Model* instance)
{
    return MODIFY_INSTANCE_OK;
}

Invoke_Method_Status Model_Provider::stub(
    const Model* self,
    const Property<String>& w,
    const Property<uint32>& x,
    Property<boolean>& y,
    Property<real32>& z,
    Property<String>& return_value)
{
    printf("Model_Provider::stub()\n");

    y.value = true;
    z.value = 555.555;
    return_value.value = "return me";

    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Model_Provider::stub2(
    const Property<String>& w,
    const Property<uint32>& x,
    Property<boolean>& y,
    Property<real32>& z,
    Property<String>& return_value)
{
    printf("Model_Provider::stub2()\n");

    y.value = true;
    z.value = 555.555;
    return_value.value = "return me";

    return INVOKE_METHOD_OK;
}

int Model_Provider::proc(
    int operation, void* arg0, void* arg1, void* arg2, void* arg3)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef Model Class;
    typedef Model_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(
            operation, arg0, arg1, arg2, arg3);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "stub") == 0)
    {
        typedef Model_stub_method Method;
        Method* method = (Method*)arg2;
        return provider->stub(
            self,
            method->w,
            method->x,
            method->y,
            method->z,
            method->return_value);
    }
    if (strcasecmp(meth_name, "stub2") == 0)
    {
        typedef Model_stub2_method Method;
        Method* method = (Method*)arg2;
        return provider->stub2(
            method->w,
            method->x,
            method->y,
            method->z,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
