// Generated by genprov 1.0.11
#include "CMPL_Time_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CMPL_Time_Provider::CMPL_Time_Provider()
{
}

CMPL_Time_Provider::~CMPL_Time_Provider()
{
}

Load_Status CMPL_Time_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CMPL_Time_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CMPL_Time_Provider::get_instance(
    const CMPL_Time* model,
    CMPL_Time*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CMPL_Time_Provider::enum_instances(
    const CMPL_Time* model,
    Enum_Instances_Handler<CMPL_Time>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CMPL_Time_Provider::create_instance(
    CMPL_Time* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CMPL_Time_Provider::delete_instance(
    const CMPL_Time* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CMPL_Time_Provider::modify_instance(
    const CMPL_Time* model,
    const CMPL_Time* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status CMPL_Time_Provider::SetTime(
    const Property<Datetime>& Time,
    Property<uint32>& return_value)
{
    // Time.value.print();
    _Time = Time;

    // Datetime dt = Time.value;

    return_value.set(1000);
    return INVOKE_METHOD_OK;
}

Invoke_Method_Status CMPL_Time_Provider::GetTime(
    Property<Datetime>& Time,
    Property<uint32>& return_value)
{
    Time = _Time;

    return_value.set(1000);
    return INVOKE_METHOD_OK;
}

/*@END@*/

CIMPLE_NAMESPACE_END
