#ifndef _Arrays_Provider_h
#define _Arrays_Provider_h

#include <cimple/cimple.h>
#include "Arrays.h"

CIMPLE_NAMESPACE_BEGIN

class Arrays_Provider
{
public:

    typedef Arrays Class;

    Arrays_Provider();

    ~Arrays_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Arrays* model,
	Arrays*& instance);

    Enum_Instances_Status enum_instances(
	const Arrays* model,
	Enum_Instances_Handler<Arrays>* handler);

    Create_Instance_Status create_instance(
	const Arrays* instance);

    Delete_Instance_Status delete_instance(
	const Arrays* instance);

    Modify_Instance_Status modify_instance(
	const Arrays* instance);

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

#endif /* _Arrays_Provider_h */
