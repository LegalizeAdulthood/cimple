#include "RefArray_Provider.h"

CIMPLE_NAMESPACE_BEGIN

RefArray_Provider::RefArray_Provider()
{
}

RefArray_Provider::~RefArray_Provider()
{
}

Load_Status RefArray_Provider::load()
{
    return LOAD_OK;
}

Unload_Status RefArray_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status RefArray_Provider::get_instance(
    const RefArray* model,
    RefArray*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status RefArray_Provider::enum_instances(
    const RefArray* model,
    Enum_Instances_Handler<RefArray>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status RefArray_Provider::create_instance(
    RefArray* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status RefArray_Provider::delete_instance(
    const RefArray* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status RefArray_Provider::modify_instance(
    const RefArray* model,
    const RefArray* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status RefArray_Provider::SendRefArray(
    const RefArray* self,
    const Property< Array<RefArrayParam*> >& arr1,
    Property< Array<RefArrayParam*> >& arr2,
    Property<uint32>& return_value)
{
    arr2.clear();

    for (size_t i = 0; i < arr1.value.size(); i++)
        arr2.value.append(arr1.value[i]->clone());

    arr2.null = false;
    return_value.set(123);

    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END
