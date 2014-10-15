#ifndef _Super_Provider_h
#define _Super_Provider_h

#include <cimple/cimple.h>
#include "Super.h"

CIMPLE_NAMESPACE_BEGIN

class Super_Provider
{
public:

    typedef Super Class;

    Super_Provider();

    ~Super_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Super* model,
	Super*& instance);

    Enum_Instances_Status enum_instances(
	const Super* model,
	Enum_Instances_Handler<Super>* handler);

    Create_Instance_Status create_instance(
	const Super* instance);

    Delete_Instance_Status delete_instance(
	const Super* instance);

    Modify_Instance_Status modify_instance(
	const Super* instance);

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

#endif /* _Super_Provider_h */
