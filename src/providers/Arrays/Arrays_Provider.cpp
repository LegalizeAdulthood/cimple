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
    const Arrays* model,
    const Arrays* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Arrays/Arrays_Provider.cpp,v 1.6 2007/04/18 03:28:48 mbrasher-public Exp $");
