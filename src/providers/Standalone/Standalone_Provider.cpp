#include "Standalone_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Standalone_Provider::Standalone_Provider()
{
}

Standalone_Provider::~Standalone_Provider()
{
}

Load_Status Standalone_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Standalone_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Standalone_Provider::get_instance(
    const Standalone* model,
    Standalone*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Standalone_Provider::enum_instances(
    const Standalone* model,
    Enum_Instances_Handler<Standalone>* handler)
{
    Standalone* instance;

    instance = Standalone::create();
    instance->key.value = 1000;
    handler->handle(instance);

    instance = Standalone::create();
    instance->key.value = 2000;
    handler->handle(instance);

    instance = Standalone::create();
    instance->key.value = 3000;
    handler->handle(instance);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Standalone_Provider::create_instance(
    const Standalone* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Standalone_Provider::delete_instance(
    const Standalone* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Standalone_Provider::modify_instance(
    const Standalone* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Standalone_Provider::proc(
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

    typedef Standalone Class;
    typedef Standalone_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Standalone/Standalone_Provider.cpp,v 1.2 2007/03/07 20:25:16 mbrasher-public Exp $");
