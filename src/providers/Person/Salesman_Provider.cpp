#include "Salesman_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Salesman_Provider::Salesman_Provider()
{
}

Salesman_Provider::~Salesman_Provider()
{
}

Load_Status Salesman_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Salesman_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Salesman_Provider::get_instance(
    const Salesman* model,
    Salesman*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Salesman_Provider::enum_instances(
    const Salesman* model,
    Enum_Instances_Handler<Salesman>* handler)
{
    {
        Salesman* instance = Salesman::create();
        instance->ssn.value = 100;
        instance->first.value = "John";
        instance->last.value = "Smith";
        handler->handle(instance);
    }

    {
        Salesman* instance = Salesman::create();
        instance->ssn.value = 200;
        instance->first.value = "John";
        instance->last.value = "Doe";
        handler->handle(instance);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Salesman_Provider::create_instance(
    const Salesman* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Salesman_Provider::delete_instance(
    const Salesman* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Salesman_Provider::modify_instance(
    const Salesman* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Salesman_Provider::proc(
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

    typedef Salesman Class;
    typedef Salesman_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Person/Salesman_Provider.cpp,v 1.2 2007/03/07 20:19:49 mbrasher-public Exp $");
