#include "Test2_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Test2_Provider::Test2_Provider()
{
}

Test2_Provider::~Test2_Provider()
{
}

Load_Status Test2_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Test2_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Test2_Provider::get_instance(
    const Test2* model,
    Test2*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Test2_Provider::enum_instances(
    const Test2* model,
    Enum_Instances_Handler<Test2>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Test2_Provider::create_instance(
    const Test2* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Test2_Provider::delete_instance(
    const Test2* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Test2_Provider::modify_instance(
    const Test2* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Test2_Provider::proc(
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

    typedef Test2 Class;
    typedef Test2_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
