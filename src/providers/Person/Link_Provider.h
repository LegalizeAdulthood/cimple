#ifndef _Link_Provider_h
#define _Link_Provider_h

#include <cimple/cimple.h>
#include "Link.h"

CIMPLE_NAMESPACE_BEGIN

class Link_Provider
{
public:

    typedef Link Class;

    Link_Provider();

    ~Link_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Link* model,
	Link*& instance);

    Enum_Instances_Status enum_instances(
	const Link* model,
	Enum_Instances_Handler<Link>* handler);

    Create_Instance_Status create_instance(
	const Link* instance);

    Delete_Instance_Status delete_instance(
	const Link* instance);

    Modify_Instance_Status modify_instance(
	const Link* instance);

    Enum_Associator_Names_Status enum_associator_names(
	const Instance* instance,
	const String& result_class,
	const String& role,
	const String& result_role,
	Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
	const Instance* instance,
	const Link* model,
	const String& role,
	Enum_References_Handler<Link>* handler);

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

    Instance_Map<Link> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Link_Provider_h */
