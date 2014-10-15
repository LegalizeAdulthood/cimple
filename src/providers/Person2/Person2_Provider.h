#ifndef _Person2_Provider_h
#define _Person2_Provider_h

#include <cimple/cimple.h>
#include "Person2.h"

CIMPLE_NAMESPACE_BEGIN

class Person2_Provider
{
public:

    typedef Person2 Class;

    Person2_Provider();

    CIMPLE_HIDE ~Person2_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Person2* model, 
	Person2*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Person2* model, 
	Enum_Instances_Handler<Person2>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Person2* inst);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Person2* inst);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Person2* inst);

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
    Instance_Map<Person2> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Person2_Provider_h */
