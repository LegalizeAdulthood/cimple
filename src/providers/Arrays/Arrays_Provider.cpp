#include "Arrays_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Arrays_Provider::Arrays_Provider()
{
}

Arrays_Provider::~Arrays_Provider()
{
}

Load_Status Arrays_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Arrays_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Arrays_Provider::get_instance(
    const Arrays* model,
    Arrays*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Arrays_Provider::enum_instances(
    const Arrays* model,
    Enum_Instances_Handler<Arrays>* handler)
{
    Arrays* arrays = Arrays::create();

    arrays->key.value = "array-one";

    Array<uint16> arr;

    for (uint16 i = 0; i < 100; i++)
	arr.append(i);

    arrays->arr.value = arr;

    handler->handle(arrays);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Arrays_Provider::create_instance(
    const Arrays* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Arrays_Provider::delete_instance(
    const Arrays* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Arrays_Provider::modify_instance(
    const Arrays* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Arrays_Provider::proc(
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

    typedef Arrays Class;
    typedef Arrays_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
