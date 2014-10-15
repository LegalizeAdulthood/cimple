#include "CMPL_Right_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CMPL_Right_Provider::CMPL_Right_Provider()
{
}

CMPL_Right_Provider::~CMPL_Right_Provider()
{
}

Load_Status CMPL_Right_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CMPL_Right_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CMPL_Right_Provider::get_instance(
    const CMPL_Right* model,
    CMPL_Right*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CMPL_Right_Provider::enum_instances(
    const CMPL_Right* model,
    Enum_Instances_Handler<CMPL_Right>* handler)
{
    CMPL_Right* right = CMPL_Right::create();
    right->key.value = 100;
    handler->handle(right);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CMPL_Right_Provider::create_instance(
    const CMPL_Right* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CMPL_Right_Provider::delete_instance(
    const CMPL_Right* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CMPL_Right_Provider::modify_instance(
    const CMPL_Right* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int CMPL_Right_Provider::proc(
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

    typedef CMPL_Right Class;
    typedef CMPL_Right_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/CMPL_Right_Provider.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
