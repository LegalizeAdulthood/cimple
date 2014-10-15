#include "Link_Provider.h"
#include "Person.h"

CIMPLE_NAMESPACE_BEGIN

static Link* _make_link(uint32 parent_ssn, uint32 child_ssn)
{
    Link* link = Link::create();

    link->parent = Person::create();
    link->parent->ssn.value = parent_ssn;

    link->child = Person::create();
    link->child->ssn.value = child_ssn;

    return link;
}

Link_Provider::Link_Provider()
{
}

Link_Provider::~Link_Provider()
{
}

Load_Status Link_Provider::load()
{
    _map.insert(_make_link(1, 3));
    _map.insert(_make_link(1, 4));
    _map.insert(_make_link(2, 3));
    _map.insert(_make_link(2, 4));

    return LOAD_OK;
}

Unload_Status Link_Provider::unload()
{
    _map.clear();
    return UNLOAD_OK;
}

Get_Instance_Status Link_Provider::get_instance(
    const Link* model, 
    Link*& instance)
{
    Link* link = _map.lookup(model);

    if (link)
    {
        instance = link->clone();
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Link_Provider::enum_instances(
    const Link* model, 
    Enum_Instances_Handler<Link>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
        handler->handle(_map[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Link_Provider::create_instance(const Link* instance)
{
    if (_map.find(instance) != size_t(-1))
        return CREATE_INSTANCE_DUPLICATE;

    print(instance);

    _map.insert(instance->clone());

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status Link_Provider::delete_instance(const Link* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return DELETE_INSTANCE_NOT_FOUND;

    destroy(_map[pos]);
    _map.remove(pos);

    return DELETE_INSTANCE_OK;
}

Modify_Instance_Status Link_Provider::modify_instance(const Link* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return MODIFY_INSTANCE_NOT_FOUND;

    copy(_map[pos], instance);

    return MODIFY_INSTANCE_OK;
}

Enum_Associator_Names_Status Link_Provider::enum_associator_names(
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

Enum_References_Status Link_Provider::enum_references(
    const Instance* instance,
    const Link* model,
    const String& role,
    Enum_References_Handler<Link>* handler)
{
    // Return unsupported, causing the caller will use enum_instances() 
    // to implement this operation.
    return ENUM_REFERENCES_UNSUPPORTED;
}

int Link_Provider::proc(
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

    typedef Link Class;
    typedef Link_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}


CIMPLE_NAMESPACE_END
