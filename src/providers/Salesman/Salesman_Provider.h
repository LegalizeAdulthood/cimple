#ifndef _Salesman_Provider_h
#define _Salesman_Provider_h

#include <cimple/cimple.h>
#include "Salesman.h"

CIMPLE_NAMESPACE_BEGIN

class Salesman_Provider
{
public:

    typedef Salesman Class;

    Salesman_Provider();

    CIMPLE_HIDE ~Salesman_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Salesman* model,
	Salesman*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Salesman* model,
	Enum_Instances_Handler<Salesman>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Salesman* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Salesman* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Salesman* instance);

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
};

CIMPLE_NAMESPACE_END

#endif /* _Salesman_Provider_h */
