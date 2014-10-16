#include "Link2_Provider.h"
#include "Person2.h"

CIMPLE_NAMESPACE_BEGIN

static Link2* _make_link(uint32 parent_ssn, uint32 child_ssn)
{
    Link2* link = Link2::create();

    link->parent = Person2::create();
    link->parent->ssn.value = parent_ssn;

    link->child = Person2::create();
    link->child->ssn.value = child_ssn;

    return link;
}

Link2_Provider::Link2_Provider()
{
}

Link2_Provider::~Link2_Provider()
{
}

Load_Status Link2_Provider::load()
{
    _map.insert(_make_link(1, 3));
    _map.insert(_make_link(1, 4));
    _map.insert(_make_link(2, 3));
    _map.insert(_make_link(2, 4));

    return LOAD_OK;
}

Unload_Status Link2_Provider::unload()
{
    _map.clear();
    return UNLOAD_OK;
}

Get_Instance_Status Link2_Provider::get_instance(
    const Link2* model,
    Link2*& instance)
{
    Link2* link = _map.lookup(model);

    if (link)
    {
        instance = link->clone();
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Link2_Provider::enum_instances(
    const Link2* model,
    Enum_Instances_Handler<Link2>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
        handler->handle(_map[i]->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Link2_Provider::create_instance(const Link2* instance)
{
    if (_map.find(instance) != size_t(-1))
        return CREATE_INSTANCE_DUPLICATE;

    print(instance);

    _map.insert(instance->clone());

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status Link2_Provider::delete_instance(const Link2* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return DELETE_INSTANCE_NOT_FOUND;

    destroy(_map[pos]);
    _map.remove(pos);

    return DELETE_INSTANCE_OK;
}

Modify_Instance_Status Link2_Provider::modify_instance(const Link2* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return MODIFY_INSTANCE_NOT_FOUND;

    copy(_map[pos], instance);

    return MODIFY_INSTANCE_OK;
}

Enum_Associator_Names_Status Link2_Provider::enum_associator_names(
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

Enum_References_Status Link2_Provider::enum_references(
    const Instance* instance,
    const Link2* model,
    const String& role,
    Enum_References_Handler<Link2>* handler)
{
    // Return unsupported, causing the caller will use enum_instances()
    // to implement this operation.
    return ENUM_REFERENCES_UNSUPPORTED;
}

int Link2_Provider::proc(
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

    typedef Link2 Class;
    typedef Link2_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}


CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Person2/Link2_Provider.cpp,v 1.3 2007/03/07 20:25:27 mbrasher-public Exp $");
