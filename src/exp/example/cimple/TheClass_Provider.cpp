#include "TheClass_Provider.h"

CIMPLE_NAMESPACE_BEGIN

TheClass_Provider::TheClass_Provider()
{
}

TheClass_Provider::~TheClass_Provider()
{
}

Load_Status TheClass_Provider::load()
{
    return LOAD_OK;
}

Unload_Status TheClass_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status TheClass_Provider::get_instance(TheClass* inst)
{
    if (inst->u.value == "TheClass01")
    {
        inst->v.value = 99;
        inst->w.value = true;
        inst->x.value = 1.5;
        inst->y.value.append(1);
        inst->y.value.append(2);
        inst->y.value.append(3);

        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instance_Status TheClass_Provider::enum_instance(TheClass* inst, State& state)
{
    return ENUM_INSTANCE_FAILED;
}

Create_Instance_Status TheClass_Provider::create_instance(const TheClass* inst)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status TheClass_Provider::delete_instance(const TheClass* inst)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status TheClass_Provider::modify_instance(const TheClass* inst)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status TheClass_Provider::add(
    const TheClass* self,
    const Property<uint32>& x,
    const Property<uint32>& y,
    Property<uint32>& return_value)
{
    return_value.value = x.value + y.value;
    return INVOKE_METHOD_OK;
}

int TheClass_Provider::proc(
    int operation, void* arg0, void* arg1, void* arg2)
{
    typedef TheClass Class;
    typedef TheClass_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(
            operation, arg0, arg1, arg2);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "add") == 0)
    {
        typedef TheClass_add_method Method;
        Method* method = (Method*)arg2;
        return provider->add(
            self,
            method->x,
            method->y,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
