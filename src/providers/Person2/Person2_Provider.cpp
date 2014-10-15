#include "Person2_Provider.h"
#include "Fan.h"

CIMPLE_NAMESPACE_BEGIN

Person2_Provider::Person2_Provider()
{
}

Person2_Provider::~Person2_Provider()
{
}

Load_Status Person2_Provider::load()
{
    {
	Person2* instance = Person2::create();
	instance->ssn.value = 1;
	instance->first.value = "Mike";
	instance->last.value = "Brasher";
	_person1 = instance;
    }

    {
	Person2* instance = Person2::create();
	instance->ssn.value = 2;
	instance->first.value = "Saara";
	instance->last.value = "Silva-Brasher";
	_person2 = instance;
    }

    {
	Person2* instance = Person2::create();
	instance->ssn.value = 3;
	instance->first.value = "Sofia";
	instance->last.value = "Brasher";
	_person3 = instance;
    }

    {
	Person2* instance = Person2::create();
	instance->ssn.value = 4;
	instance->first.value = "Andrea";
	instance->last.value = "Brasher";
	_person4 = instance;
    }

    return LOAD_OK;
}

Unload_Status Person2_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Person2_Provider::get_instance(
    const Person2* model, 
    Person2*& instance)
{
    switch (model->ssn.value)
    {
	case 1:
	    instance = _person1->clone();
	    return GET_INSTANCE_OK;
	case 2:
	    instance = _person2->clone();
	    return GET_INSTANCE_OK;
	case 3:
	    instance = _person3->clone();
	    return GET_INSTANCE_OK;
	case 4:
	    instance = _person4->clone();
	    return GET_INSTANCE_OK;
	default:
	    return GET_INSTANCE_NOT_FOUND;
    }
}

Enum_Instances_Status Person2_Provider::enum_instances(
    const Person2* model, 
    Enum_Instances_Handler<Person2>* handler)
{
    handler->handle(_person1->clone());
    handler->handle(_person2->clone());
    handler->handle(_person3->clone());
    handler->handle(_person4->clone());

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Person2_Provider::create_instance(
    const Person2* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Person2_Provider::delete_instance(
    const Person2* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Person2_Provider::modify_instance(
    const Person2* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Person2_Provider::proc(
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

    typedef Person2 Class;
    typedef Person2_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
