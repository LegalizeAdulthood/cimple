#include "Methods_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Methods_Provider::Methods_Provider()
{
}

Methods_Provider::~Methods_Provider()
{
}

Load_Status Methods_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Methods_Provider::unload()
{
    return UNLOAD_OK;
}

Timer_Status Methods_Provider::timer(uint64& timeout)
{
    return TIMER_CANCEL;
}

Get_Instance_Status Methods_Provider::get_instance(
    const Methods* model,
    Methods*& instance)
{
    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Methods_Provider::enum_instances(
    const Methods* model,
    Enum_Instances_Handler<Methods>* handler)
{
    return ENUM_INSTANCES_FAILED;
}

Create_Instance_Status Methods_Provider::create_instance(
    const Methods* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Methods_Provider::delete_instance(
    const Methods* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Methods_Provider::modify_instance(
    const Methods* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Methods_Provider::foo(
    const Methods* self,
    const Property<uint32>& arg1,
    const Property<String>& arg2,
    const Property<boolean>& arg3,
    Property<uint32>& arg4,
    Property<String>& arg5,
    Property<boolean>& arg6,
    Property<String>& return_value)
{
#if 0
    printf("===== Methods_Provider::foo()\n");
    printf("[in] arg1: %u\n", arg1.value);
    printf("[in] arg2: %s\n", arg2.value.c_str());
    printf("[in] arg3: %s\n", arg3.value ? "true" : "false");
#endif

    arg4.null = false;
    arg4.value = 999;

    arg5.null = false;
    arg5.value = "nine hundred ninety-nine";

    arg6.null = false;
    arg6.value = false;

    return_value.null = false;
    return_value.value = "thanks for calling";

    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Methods_Provider::foo2(
    const Methods* self,
    const Arg* arg1,
    Arg* arg2,
    Property<String>& return_value)
{
    if (arg2)
    {
	arg2->key.value = 12345;
	arg2->key.null = false;

	return_value.value = "thanks";
	return_value.null = false;
	return INVOKE_METHOD_OK;
    }

    return INVOKE_METHOD_FAILED;
}

int Methods_Provider::proc(
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

    typedef Methods Class;
    typedef Methods_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(
	    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo") == 0)
    {
        typedef Methods_foo_method Method;
        Method* method = (Method*)arg2;
        return provider->foo(
            self,
            method->arg1,
            method->arg2,
            method->arg3,
            method->arg4,
            method->arg5,
            method->arg6,
            method->return_value);
    }
    if (strcasecmp(meth_name, "foo2") == 0)
    {
        typedef Methods_foo2_method Method;
        Method* method = (Method*)arg2;
        return provider->foo2(
            self,
            method->arg1,
            method->arg2,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
