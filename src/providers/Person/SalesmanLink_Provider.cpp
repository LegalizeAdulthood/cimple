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
    SalesmanLink* link = SalesmanLink::create();

    link->parent = Salesman::create();
    link->parent->ssn.value = 100;

    link->child = Salesman::create();
    link->child->ssn.value = 200;

    handler->handle(link);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status SalesmanLink_Provider::create_instance(
    SalesmanLink* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status SalesmanLink_Provider::delete_instance(
    const SalesmanLink* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status SalesmanLink_Provider::modify_instance(
    const SalesmanLink* model,
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
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status SalesmanLink_Provider::enum_references(
    const Instance* instance,
    const SalesmanLink* model,
    const String& role,
    Enum_References_Handler<SalesmanLink>* handler)
{
    assert(instance && instance->__magic == CIMPLE_INSTANCE_MAGIC);
    assert(model && model->__magic == CIMPLE_INSTANCE_MAGIC);

    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status SalesmanLink_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATORS_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

