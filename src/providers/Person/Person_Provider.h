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

    ~Person_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Person* model, 
	Person*& instance);

    Enum_Instances_Status enum_instances(
	const Person* model, 
	Enum_Instances_Handler<Person>* handler);

    Create_Instance_Status create_instance(
	const Person* inst);

    Delete_Instance_Status delete_instance(
	const Person* inst);

    Modify_Instance_Status modify_instance(
	const Person* inst);

    static int proc(
	const Registration* registration,
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
    Thread _thread;
    Atomic_Counter _stop;
};

CIMPLE_NAMESPACE_END

#endif /* _Person_Provider_h */
