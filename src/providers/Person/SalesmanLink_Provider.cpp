#include "SalesmanLink_Provider.h"

CIMPLE_NAMESPACE_BEGIN

SalesmanLink_Provider::SalesmanLink_Provider()
{
}

SalesmanLink_Provider::~SalesmanLink_Provider()
{
}

Load_Status SalesmanLink_Provider::load()
{
    return LOAD_OK;
}

Unload_Status SalesmanLink_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status SalesmanLink_Provider::get_instance(
    const SalesmanLink* model,
    SalesmanLink*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status SalesmanLink_Provider::enum_instances(
    const SalesmanLink* model,
    Enum_Instances_Handler<SalesmanLink>* handler)
{
    printf("***** SalesmanLink_Provider::enum_instances()\n");

    SalesmanLink* link = SalesmanLink::create();

    link->parent = Person::create();
    link->parent->ssn.value = 100;

    link->child = Person::create();
    link->child->ssn.value = 200;

    handler->handle(link);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status SalesmanLink_Provider::create_instance(
    const SalesmanLink* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status SalesmanLink_Provider::delete_instance(
    const SalesmanLink* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status SalesmanLink_Provider::modify_instance(
    const SalesmanLink* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status SalesmanLink_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    printf("***** SalesmanLink_Provider::enum_associator_names()\n");
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status SalesmanLink_Provider::enum_references(
    const Instance* instance,
    const SalesmanLink* model,
    const String& role,
    Enum_References_Handler<SalesmanLink>* handler)
{
    printf("***** SalesmanLink_Provider::enum_references()\n");
    assert(instance && instance->__magic == CIMPLE_INSTANCE_MAGIC);
    assert(model && model->__magic == CIMPLE_INSTANCE_MAGIC);

    return ENUM_REFERENCES_UNSUPPORTED;
}

int SalesmanLink_Provider::proc(
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

    typedef SalesmanLink Class;
    typedef SalesmanLink_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration, 
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Person/SalesmanLink_Provider.cpp,v 1.3 2007/03/07 20:19:49 mbrasher-public Exp $");
