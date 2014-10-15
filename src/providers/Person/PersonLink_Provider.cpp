/*
    This provider is based completely on the Instance_Map.
    Objects are built at initialization and the one line MAP
    operation calls used to retrieve them for the various operations.
 
    This provider can process all of the CIM Intrinsic operations for
    instanceand assocation provider types
 
    All of the Association operations default to use the enumerate
    and internal CIMPLE association/reference filtering.
*/
#include "PersonLink_Provider.h"
#include "Person.h"

CIMPLE_NAMESPACE_BEGIN

// Create a single instance of the association instance
static PersonLink* _make_link(uint32 parent_ssn, uint32 child_ssn)
{
    PersonLink* link = PersonLink::create();

    link->parent = Person::create();
    link->parent->ssn.value = parent_ssn;

    link->child = Person::create();
    link->child->ssn.value = child_ssn;

    return link;
}

PersonLink_Provider::PersonLink_Provider()
{
}

PersonLink_Provider::~PersonLink_Provider()
{
}

Load_Status PersonLink_Provider::load()
{
    // Build all of the links and put into the map.
    _map.insert(_make_link(1, 3));
    _map.insert(_make_link(1, 4));
    _map.insert(_make_link(1, 5));
    _map.insert(_make_link(2, 3));
    _map.insert(_make_link(2, 4));
    _map.insert(_make_link(2, 5));

    return LOAD_OK;
}

Unload_Status PersonLink_Provider::unload()
{
    _map.clear();
    return UNLOAD_OK;
}

Get_Instance_Status PersonLink_Provider::get_instance(
    const PersonLink* model, 
    PersonLink*& instance)
{
    // This is more efficient than using NOT_SUPPORTED
    return _map.get_instance(model, instance);
}

Enum_Instances_Status PersonLink_Provider::enum_instances(
    const PersonLink* model, 
    Enum_Instances_Handler<PersonLink>* handler)
{
    return _map.enum_instances(model, handler);
}

Create_Instance_Status PersonLink_Provider::create_instance(
    PersonLink* instance)
{
    return _map.create_instance(instance);
}

Delete_Instance_Status PersonLink_Provider::delete_instance(
    const PersonLink* instance)
{
    return _map.delete_instance(instance);
}

Modify_Instance_Status PersonLink_Provider::modify_instance(
    const PersonLink* model,
    const PersonLink* instance)
{
    return _map.modify_instance(model, instance);
}

Enum_Associator_Names_Status PersonLink_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    // Return unsupported, causing the caller will use enum_instances() 
    // to implement this operation.
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status PersonLink_Provider::enum_references(
    const Instance* instance,
    const PersonLink* model,
    const String& role,
    Enum_References_Handler<PersonLink>* handler)
{
    assert(instance && instance->__magic == CIMPLE_INSTANCE_MAGIC);
    assert(model && model->__magic == CIMPLE_INSTANCE_MAGIC);

    // Return unsupported, causing the caller will use enum_instances() 
    // to implement this operation.
    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status PersonLink_Provider::enum_associators(
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

