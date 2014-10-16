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

Timer_Status Link_Provider::timer(uint64& timeout_msec)
{
    return TIMER_CANCEL;
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
    {
        if (!handler->handle(_map[i]->clone()))
            break;
    }

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

int Link_Provider::proc(
    int operation, void* arg0, void* arg1, void* arg2, void* arg3)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY
    // GENERATED.

    typedef Link Class;
    typedef Link_Provider Provider;
    return Provider_Proc_T<Provider>::proc(operation, arg0, arg1, arg2, arg3);
}

CIMPLE_NAMESPACE_END
