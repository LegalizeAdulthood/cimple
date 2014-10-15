#ifndef _Person_Provider_h
#define _Person_Provider_h

#include <cimple/cimple.h>
#include "Person.h"

CIMPLE_NAMESPACE_BEGIN

class Person_Provider
{
public:

    typedef Person Class;

    Person_Provider();

    CIMPLE_HIDE ~Person_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Person* model, 
	Person*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Person* model, 
	Enum_Instances_Handler<Person>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Person* inst);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Person* inst);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Person* inst);

    static CIMPLE_HIDE int proc(
	int operation, 
	void* arg0, 
	void* arg1, 
	void* arg2, 
	void* arg3,
	void* arg4, 
	void* arg5, 
	void* arg6, 
	void* arg7);

private:
    Instance_Map<Person> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Person_Provider_h */
