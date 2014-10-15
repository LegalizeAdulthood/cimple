#include "Arrays_Provider.h"

/*
    Array provider only supports enumerate and get.  The purpose of this
    provider is to demonstrate building of array properties in responses
*/

CIMPLE_NAMESPACE_BEGIN

Arrays_Provider::Arrays_Provider()
{
}

Arrays_Provider::~Arrays_Provider()
{
}

Load_Status Arrays_Provider::load()
{
    // set default size of arrays to return
    _returnCount = 100;
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
    uint32 returnCount = _returnCount;
    Arrays* arrays = Arrays::create();

    arrays->key.value = "array-one";

    arrays->returnCount.value = returnCount;

    // Builds a separate array and assigns the built array to the
    // property
    Array<uint16> arr;
    for (uint16 i = 0; i < returnCount; i++)
        arr.append(i);
    arrays->arr.value = arr;

    // Easier, append directly to the array property
    for (uint32 i = 0; i < returnCount; i++)
    {
        arrays->arr_uint32.value.append(i);
        arrays->arrString.value.append(string_printf("%u", i));
    }

    handler->handle(arrays);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Arrays_Provider::create_instance(
    Arrays* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Arrays_Provider::delete_instance(
    const Arrays* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Arrays_Provider::modify_instance(
    const Arrays* model,
    const Arrays* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Arrays_Provider::setReturnCount(
    const Arrays* self,
    const Property<uint32>& returnCount,
    Property<uint32>& prevReturnCount,
    Property<uint32>& return_value)

{
    return_value.null = false;

    prevReturnCount.null = false;
    prevReturnCount.value = _returnCount;

    if (returnCount.null == false)
    {
        _returnCount = returnCount.value;
        return_value.value = 0;
    }
    // if no input param, set return to 1
    else
    {
        return_value.value = 1;
    }

    return INVOKE_METHOD_OK;}

Invoke_Method_Status Arrays_Provider::getReturnCount(
    const Arrays* self,
    Property<uint32>& returnCount,
    Property<uint32>& return_value)

{
    return INVOKE_METHOD_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

