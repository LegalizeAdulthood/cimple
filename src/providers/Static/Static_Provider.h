#ifndef _Static_Provider_h
#define _Static_Provider_h

#include <cimple/cimple.h>
#include "Static.h"

CIMPLE_NAMESPACE_BEGIN

class Static_Provider
{
public:

    typedef Static Class;

    Static_Provider();

    ~Static_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Static* model,
	Static*& instance);

    Enum_Instances_Status enum_instances(
	const Static* model,
	Enum_Instances_Handler<Static>* handler);

    Create_Instance_Status create_instance(
	const Static* instance);

    Delete_Instance_Status delete_instance(
	const Static* instance);

    Modify_Instance_Status modify_instance(
	const Static* instance);

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

#endif /* _Static_Provider_h */
