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
    const CMPL_Left* model,
    const CMPL_Left* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/CMPL_Left_Provider.cpp,v 1.4 2007/04/18 03:51:25 mbrasher-public Exp $");
