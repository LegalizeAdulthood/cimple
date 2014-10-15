#include "Person_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Person_Provider::Person_Provider()
{
}

Person_Provider::~Person_Provider()
{
}

Load_Status Person_Provider::load()
{
    {
        Person* instance = Person::create();
        instance->ssn.value = 1;
        instance->first.value = "Mike";
        instance->last.value = "Brasher";
        _map.insert(instance);
    }

    {
        Person* instance = Person::create();
        instance->ssn.value = 2;
        instance->first.value = "Saara";
        instance->last.value = "Silva-Brasher";
        _map.insert(instance);
    }

    {
        Person* instance = Person::create();
        instance->ssn.value = 3;
        instance->first.value = "Sofia";
        instance->last.value = "Brasher";
        _map.insert(instance);
    }

    {
        Person* instance = Person::create();
        instance->ssn.value = 4;
        instance->first.value = "Andrea";
        instance->last.value = "Brasher";
        _map.insert(instance);
    }

    return LOAD_OK;
}

Unload_Status Person_Provider::unload()
{
#if USE_THREAD
    _stop.inc();
    void* value_ptr = 0;
    Thread::join(_thread, value_ptr);
#endif

    _map.clear();

    return UNLOAD_OK;
}

Get_Instance_Status Person_Provider::get_instance(
    const Person* model, 
    Person*& instance)
{
    Person* person = _map.lookup(model);

    if (person)
    {
        instance = person->clone();
        return GET_INSTANCE_OK;
    }

    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status Person_Provider::enum_instances(
    const Person* model, 
    Enum_Instances_Handler<Person>* handler)
{
    for (size_t i = 0; i < _map.size(); i++)
    {
        Person* person = _map[i]->clone();
        handler->handle(person);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Person_Provider::create_instance(
    Person* instance)
{
    if (_map.find(instance) != size_t(-1))
        return CREATE_INSTANCE_DUPLICATE;

    _map.insert(instance->clone());

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status Person_Provider::delete_instance(const Person* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return DELETE_INSTANCE_NOT_FOUND;

    _map.remove(pos);

    return DELETE_INSTANCE_OK;
}

Modify_Instance_Status Person_Provider::modify_instance(
    const Person* model,
    const Person* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
        return MODIFY_INSTANCE_NOT_FOUND;

    copy(_map[pos], instance);

    return MODIFY_INSTANCE_OK;
}

CIMPLE_NAMESPACE_END

