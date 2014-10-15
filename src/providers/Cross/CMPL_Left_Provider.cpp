#include "CMPL_Left_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CMPL_Left_Provider::CMPL_Left_Provider()
{
}

CMPL_Left_Provider::~CMPL_Left_Provider()
{
}

Load_Status CMPL_Left_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CMPL_Left_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CMPL_Left_Provider::get_instance(
    const CMPL_Left* model,
    CMPL_Left*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CMPL_Left_Provider::enum_instances(
    const CMPL_Left* model,
    Enum_Instances_Handler<CMPL_Left>* handler)
{
    CMPL_Left* left = CMPL_Left::create();
    left->key.value = 100;
    handler->handle(left);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CMPL_Left_Provider::create_instance(
    const CMPL_Left* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CMPL_Left_Provider::delete_instance(
    const CMPL_Left* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CMPL_Left_Provider::modify_instance(
    const CMPL_Left* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int CMPL_Left_Provider::proc(
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

    typedef CMPL_Left Class;
    typedef CMPL_Left_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/CMPL_Left_Provider.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
