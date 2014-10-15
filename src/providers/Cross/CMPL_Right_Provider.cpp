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
    const CMPL_Right* model,
    const CMPL_Right* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/CMPL_Right_Provider.cpp,v 1.4 2007/04/18 03:51:25 mbrasher-public Exp $");
