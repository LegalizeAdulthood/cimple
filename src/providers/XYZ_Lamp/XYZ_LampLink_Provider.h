#ifndef _XYZ_LampLink_Provider_h
#define _XYZ_LampLink_Provider_h

#include <cimple/cimple.h>
#include "XYZ_LampLink.h"

CIMPLE_NAMESPACE_BEGIN

class XYZ_LampLink_Provider
{
public:

    typedef XYZ_LampLink Class;

    XYZ_LampLink_Provider();

    CIMPLE_HIDE ~XYZ_LampLink_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const XYZ_LampLink* model,
	XYZ_LampLink*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const XYZ_LampLink* model,
	Enum_Instances_Handler<XYZ_LampLink>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const XYZ_LampLink* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const XYZ_LampLink* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const XYZ_LampLink* instance);

    CIMPLE_HIDE Enum_Associator_Names_Status enum_associator_names(
	const Instance* instance,
	const String& result_class,
	const String& role,
	const String& result_role,
	Enum_Associator_Names_Handler<Instance>* handler);

    CIMPLE_HIDE Enum_References_Status enum_references(
	const Instance* instance,
	const XYZ_LampLink* model,
	const String& role,
	Enum_References_Handler<XYZ_LampLink>* handler);

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

#endif /* _XYZ_LampLink_Provider_h */
