#ifndef _Test2Link_Provider_h
#define _Test2Link_Provider_h

#include <cimple/cimple.h>
#include "Test2Link.h"

CIMPLE_NAMESPACE_BEGIN

class Test2Link_Provider
{
public:

    typedef Test2Link Class;

    Test2Link_Provider();

    ~Test2Link_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Test2Link* model,
	Test2Link*& instance);

    Enum_Instances_Status enum_instances(
	const Test2Link* model,
	Enum_Instances_Handler<Test2Link>* handler);

    Create_Instance_Status create_instance(
	const Test2Link* instance);

    Delete_Instance_Status delete_instance(
	const Test2Link* instance);

    Modify_Instance_Status modify_instance(
	const Test2Link* instance);

    Enum_Associator_Names_Status enum_associator_names(
	const Instance* instance,
	const String& result_class,
	const String& role,
	const String& result_role,
	Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
	const Instance* instance,
	const Test2Link* model,
	const String& role,
	Enum_References_Handler<Test2Link>* handler);

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

#endif /* _Test2Link_Provider_h */
