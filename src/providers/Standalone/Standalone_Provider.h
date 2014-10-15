#ifndef _Standalone_Provider_h
#define _Standalone_Provider_h

#include <cimple/cimple.h>
#include "Standalone.h"

CIMPLE_NAMESPACE_BEGIN

class Standalone_Provider
{
public:

    typedef Standalone Class;

    Standalone_Provider();

    ~Standalone_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Standalone* model,
	Standalone*& instance);

    Enum_Instances_Status enum_instances(
	const Standalone* model,
	Enum_Instances_Handler<Standalone>* handler);

    Create_Instance_Status create_instance(
	const Standalone* instance);

    Delete_Instance_Status delete_instance(
	const Standalone* instance);

    Modify_Instance_Status modify_instance(
	const Standalone* instance);

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

#endif /* _Standalone_Provider_h */
