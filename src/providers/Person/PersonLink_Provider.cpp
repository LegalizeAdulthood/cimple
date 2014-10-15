#include "PersonLink_Provider.h"
#include "Person.h"

CIMPLE_NAMESPACE_BEGIN

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
    _map.insert(_make_link(1, 3));
    _map.insert(_make_link(1, 4));
    _map.insert(_make_link(2, 3));
    _map.insert(_make_link(2, 4));

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
    PersonLink* link = _map.lookup(model);

    if (link)
    {
        instance = link->clone();
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status PersonLink_Provider::enum_instances(
    const PersonLink* model, 
    Enum_Instances_Handler<PersonLink>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
        handler->handle(_map[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status PersonLink_Provider::create_instance(
    PersonLink* instance)
{
    if (_map.find(instance) != size_t(-1))
        return CREATE_INSTANCE_DUPLICATE;

    _map.insert(instance->clone());

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status PersonLink_Provider::delete_instance(
    const PersonLink* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return DELETE_INSTANCE_NOT_FOUND;

    destroy(_map[pos]);
    _map.remove(pos);

    return DELETE_INSTANCE_OK;
}

Modify_Instance_Status PersonLink_Provider::modify_instance(
    const PersonLink* model,
    const PersonLink* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return MODIFY_INSTANCE_NOT_FOUND;

    copy(_map[pos], instance);

    return MODIFY_INSTANCE_OK;
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

