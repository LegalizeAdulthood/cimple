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
    const Salesman* model,
    const Salesman* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Person/Salesman_Provider.cpp,v 1.4 2007/04/18 03:29:40 mbrasher-public Exp $");
