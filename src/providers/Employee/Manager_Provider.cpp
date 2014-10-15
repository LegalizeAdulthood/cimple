#include "Manager_Provider.h"
#include "Resource.h"

CIMPLE_NAMESPACE_BEGIN

Manager_Provider::Manager_Provider()
{
}

Manager_Provider::~Manager_Provider()
{
}

Load_Status Manager_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Manager_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Manager_Provider::get_instance(
    const Manager* model,
    Manager*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Manager_Provider::enum_instances(
    const Manager* model,
    Enum_Instances_Handler<Manager>* handler)
{
    Auto_Mutex am(resource.mutex);

    handler->handle(resource.manager->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Manager_Provider::create_instance(
    Manager* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Manager_Provider::delete_instance(
    const Manager* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Manager_Provider::modify_instance(
    const Manager* model,
    const Manager* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Manager_Provider::SetOutOfOfficeState(
    const Manager* self,
    const Property<boolean>& OutOfOfficeState,
    Property<boolean>& PreviousOutOfOfficeState,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status Manager_Provider::GetEmployeeCount(
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END
