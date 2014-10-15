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

    ~Person2_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Person2* model, 
	Person2*& instance);

    Enum_Instances_Status enum_instances(
	const Person2* model, 
	Enum_Instances_Handler<Person2>* handler);

    Create_Instance_Status create_instance(
	const Person2* inst);

    Delete_Instance_Status delete_instance(
	const Person2* inst);

    Modify_Instance_Status modify_instance(
	const Person2* inst);

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

    Person2* _person1;
    Person2* _person2;
    Person2* _person3;
    Person2* _person4;
};

CIMPLE_NAMESPACE_END

#endif /* _Person2_Provider_h */
