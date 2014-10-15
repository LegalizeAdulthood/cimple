#ifndef _Test1_Provider_h
#define _Test1_Provider_h

#include <cimple/cimple.h>
#include "Test1.h"

CIMPLE_NAMESPACE_BEGIN

class Test1_Provider
{
public:

    typedef Test1 Class;

    Test1_Provider();

    ~Test1_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Test1* model,
	Test1*& instance);

    Enum_Instances_Status enum_instances(
	const Test1* model,
	Enum_Instances_Handler<Test1>* handler);

    Create_Instance_Status create_instance(
        Test1* instance);

    Delete_Instance_Status delete_instance(
	const Test1* instance);

    Modify_Instance_Status modify_instance(
        const Test1* model,
        const Test1* instance);

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

#endif /* _Test1_Provider_h */
