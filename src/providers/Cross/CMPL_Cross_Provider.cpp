#include "CMPL_Cross_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CMPL_Cross_Provider::CMPL_Cross_Provider()
{
}

CMPL_Cross_Provider::~CMPL_Cross_Provider()
{
}

Load_Status CMPL_Cross_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CMPL_Cross_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CMPL_Cross_Provider::get_instance(
    const CMPL_Cross* model,
    CMPL_Cross*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CMPL_Cross_Provider::enum_instances(
    const CMPL_Cross* model,
    Enum_Instances_Handler<CMPL_Cross>* handler)
{
    CMPL_Cross* cross = CMPL_Cross::create();

    cross->left = CMPL_Left::create();
    cross->left->__name_space = "root/cimv2";
    cross->left->key.value = 100;

    cross->right = CMPL_Right::create();
    cross->right->__name_space = "root/PG_InterOp";
    cross->right->key.value = 100;

    handler->handle(cross);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CMPL_Cross_Provider::create_instance(
    const CMPL_Cross* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CMPL_Cross_Provider::delete_instance(
    const CMPL_Cross* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CMPL_Cross_Provider::modify_instance(
    const CMPL_Cross* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status CMPL_Cross_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status CMPL_Cross_Provider::enum_references(
    const Instance* instance,
    const CMPL_Cross* model,
    const String& role,
    Enum_References_Handler<CMPL_Cross>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

int CMPL_Cross_Provider::proc(
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

    typedef CMPL_Cross Class;
    typedef CMPL_Cross_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration, 
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/CMPL_Cross_Provider.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
