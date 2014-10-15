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

int ModernLamp_Provider::proc(
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

    typedef ModernLamp Class;
    typedef ModernLamp_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo") == 0)
    {
        typedef ModernLamp_foo_method Method;
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
