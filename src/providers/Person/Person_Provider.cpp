#include "Person_Provider.h"
#include "Fan.h"

CIMPLE_NAMESPACE_BEGIN

static void _test_cimom_ops()
{
    Ref<Fan> fan(Fan::create());
    Instance_Enumerator e;

    printf("===== cimom::enum_instances()\n");
    
    if (cimom::enum_instances("root/cimv2", fan, e) == 0)
    {
	for (; e; e++)
	    print(e());
    }

    printf("===== cimom::get_instance()\n");

    {
	Ref<Fan> keys(Fan::create());
	keys->DeviceID.value = "FAN01";
	Ref<Instance> inst = cimom::get_instance("root/cimv2", keys);
	print(inst);
    }

    printf("===== cimom::modify_instance()\n");

    {
	Ref<Fan> inst(Fan::create());

	inst->DeviceID.value = "FAN01";
	inst->Speed.value = 1111;
	inst->DesiredSpeed.value = 1111;
	int result = cimom::modify_instance("root/cimv2", inst);

	if (result != 0)
	    printf("failed\n");
    }

    printf("===== cimom::get_instance()\n");

    {
	Ref<Fan> keys(Fan::create());
	keys->DeviceID.value = "FAN01";
	Ref<Instance> inst = cimom::get_instance("root/cimv2", keys);
	print(inst);
    }

    printf("===== cimom::delete_instance()\n");

    {
	Ref<Fan> key(Fan::create());
	key->DesiredSpeed.value = 1111;
	int result = cimom::delete_instance("root/cimv2", key);

	if (result != 0)
	    printf("cimom::delete_instance() failed\n");
    }

    printf("===== cimom::get_instance()\n");

    {
	Ref<Fan> keys(Fan::create());
	keys->DeviceID.value = "FAN01";
	Ref<Instance> inst = cimom::get_instance("root/cimv2", keys);

	if (inst)
	    print(inst);
	else
	    printf("cimom::get_instance() failed\n");
    }
}

static void* _thread_proc(void* arg)
{
    Atomic_Counter& stop = *((Atomic_Counter*)arg);

    while (stop.get() == 0)
    {
	Time::sleep(Time::SEC);
	_test_cimom_ops();
    }

    return 0;
}

Person_Provider::Person_Provider()
{
}

Person_Provider::~Person_Provider()
{
}

Load_Status Person_Provider::load()
{
#if USE_THREAD
    Thread::create_joinable(_thread, _thread_proc, &_stop);
#endif

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

Timer_Status Person_Provider::timer(uint64& timeout_msec)
{
    return TIMER_CANCEL;
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

Create_Instance_Status Person_Provider::create_instance(const Person* instance)
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

Modify_Instance_Status Person_Provider::modify_instance(const Person* instance)
{
    size_t pos = _map.find(instance);

    if (pos == size_t(-1))
	return MODIFY_INSTANCE_NOT_FOUND;

    copy(_map[pos], instance);

    return MODIFY_INSTANCE_OK;
}

int Person_Provider::proc(
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

    typedef Person Class;
    typedef Person_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
