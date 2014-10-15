#ifndef _Thing_Provider_h
#define _Thing_Provider_h

#include <cimple/cimple.h>
#include "Thing.h"

CIMPLE_NAMESPACE_BEGIN

class Thing_Provider
{
public:

    typedef Thing Class;

    Thing_Provider();

    ~Thing_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Thing* model,
	Thing*& instance);

    Enum_Instances_Status enum_instances(
	const Thing* model,
	Enum_Instances_Handler<Thing>* handler);

    Create_Instance_Status create_instance(
	const Thing* instance);

    Delete_Instance_Status delete_instance(
	const Thing* instance);

    Modify_Instance_Status modify_instance(
	const Thing* instance);

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

    Instance_Map<Thing> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Thing_Provider_h */
