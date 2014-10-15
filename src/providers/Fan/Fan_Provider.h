#ifndef _Fan_Provider_h
#define _Fan_Provider_h

#include <cimple/cimple.h>
#include "Fan.h"

CIMPLE_NAMESPACE_BEGIN

class Fan_Provider
{
public:

    typedef Fan Class;

    Fan_Provider();

    CIMPLE_HIDE ~Fan_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Fan* model,
	Fan*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Fan* model,
	Enum_Instances_Handler<Fan>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Fan* inst);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Fan* inst);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Fan* inst);

    CIMPLE_HIDE Invoke_Method_Status SetSpeed(
        const Fan* self,
        const Property<uint64>& DesiredSpeed,
        Property<uint32>& return_value);

    CIMPLE_HIDE static int proc(
	int operation, void* arg0, void* arg1, void* arg2, void* arg3);

private:

    Instance_Map<Fan> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Fan_Provider_h */
