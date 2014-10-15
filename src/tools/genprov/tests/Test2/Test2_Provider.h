#ifndef _Test2_Provider_h
#define _Test2_Provider_h

#include <cimple/cimple.h>
#include "Test2.h"

CIMPLE_NAMESPACE_BEGIN

class Test2_Provider
{
public:

    typedef Test2 Class;

    Test2_Provider();

    ~Test2_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Test2* model,
	Test2*& instance);

    Enum_Instances_Status enum_instances(
	const Test2* model,
	Enum_Instances_Handler<Test2>* handler);

    Create_Instance_Status create_instance(
	const Test2* instance);

    Delete_Instance_Status delete_instance(
	const Test2* instance);

    Modify_Instance_Status modify_instance(
	const Test2* instance);

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
};

CIMPLE_NAMESPACE_END

#endif /* _Test2_Provider_h */
