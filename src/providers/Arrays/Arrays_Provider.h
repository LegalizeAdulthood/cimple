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
        const Arrays* model,
        const Arrays* instance);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Arrays_Provider_h */
