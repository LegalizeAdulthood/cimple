#include "Methods_Provider.h"

#define TRACE /* CIMPLE_TRACE */

CIMPLE_NAMESPACE_BEGIN

Methods_Provider::Methods_Provider()
{
    TRACE;
}

Methods_Provider::~Methods_Provider()
{
    TRACE;
}

Load_Status Methods_Provider::load()
{
    TRACE;
    return LOAD_OK;
}

Unload_Status Methods_Provider::unload()
{
    TRACE;
    return UNLOAD_OK;
}

Get_Instance_Status Methods_Provider::get_instance(
    const Methods* model,
    Methods*& instance)
{
    TRACE;

    if (model->key.value == 99)
    {
        instance = Methods::create();
        instance->key.value = 99;
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Methods_Provider::enum_instances(
    const Methods* model,
    Enum_Instances_Handler<Methods>* handler)
{
    TRACE;
    Methods* methods = Methods::create();
    methods->key.value = 99;
    handler->handle(methods);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Methods_Provider::create_instance(
    Methods* instance)
{
    TRACE;
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Methods_Provider::delete_instance(
    const Methods* instance)
{
    TRACE;
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Methods_Provider::modify_instance(
    const Methods* model,
    const Methods* instance)
{
    TRACE;
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
    TRACE;
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
    const Argument* arg1,
    Argument*& arg2,
    Property<String>& return_value)
{
    TRACE;
    arg2 = Argument::create();

    arg2->key.set(12345);
//  arg2->key.value = 12345;
//  arg2->key.null = false;

    return_value.set("thanks");
//  return_value.value = "thanks";
//  return_value.null = false;

    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Methods_Provider::foo3(
    Property<String>& return_value)
{
    TRACE;
    return_value.set("goodbye");
    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Methods_Provider::foo4(
    const Methods* self,
    const Property<Array_String>& arr1,
    Property<Array_String>& arr2,
    Property<uint32>& return_value)
{
    TRACE;

    arr2 = arr1;
    // use the value and null form of setting.  Note that
    // we prefer to sue return_value.set(999) as a single statement.
    return_value.value = 999;
    return_value.null = false;

    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Methods_Provider::foo5(
    const Methods* self,
    const Property<uint32>& in_arg,
    Property<uint32>& in_out_arg,
    Property<uint32>& out_arg,
    Property<uint32>& return_value)
{
    out_arg = in_arg;
    return_value.set(1200);
    
    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Methods_Provider::junk(
    const Methods* self,
    const Property<uint32>& x,
    const Property<uint32>& y,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END
