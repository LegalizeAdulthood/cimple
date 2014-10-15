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

    CIMPLE_HIDE ~Thing_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Thing* model,
	Thing*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Thing* model,
	Enum_Instances_Handler<Thing>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Thing* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Thing* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Thing* instance);

    static CIMPLE_HIDE int proc(
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
