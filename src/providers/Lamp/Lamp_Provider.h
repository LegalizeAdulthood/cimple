#ifndef _Lamp_Provider_h
#define _Lamp_Provider_h

#include <cimple/cimple.h>
#include "Lamp.h"

CIMPLE_NAMESPACE_BEGIN

class Lamp_Provider
{
public:

    typedef Lamp Class;

    Lamp_Provider();

    CIMPLE_HIDE ~Lamp_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Lamp* model,
	Lamp*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Lamp* model,
	Enum_Instances_Handler<Lamp>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Lamp* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Lamp* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Lamp* instance);

    CIMPLE_HIDE Invoke_Method_Status foo(
        const Lamp* self,
        const Property<String>& arg1,
        const Property<String>& arg2,
        Property<uint32>& return_value);

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

    Instance_Map<Lamp> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Lamp_Provider_h */
