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

    ~XYZ_LampLink_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const XYZ_LampLink* model,
	XYZ_LampLink*& instance);

    Enum_Instances_Status enum_instances(
	const XYZ_LampLink* model,
	Enum_Instances_Handler<XYZ_LampLink>* handler);

    Create_Instance_Status create_instance(
        XYZ_LampLink* instance);

    Delete_Instance_Status delete_instance(
	const XYZ_LampLink* instance);

    Modify_Instance_Status modify_instance(
        const XYZ_LampLink* model,
        const XYZ_LampLink* instance);

    Enum_Associator_Names_Status enum_associator_names(
	const Instance* instance,
	const String& result_class,
	const String& role,
	const String& result_role,
	Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
	const Instance* instance,
	const XYZ_LampLink* model,
	const String& role,
	Enum_References_Handler<XYZ_LampLink>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _XYZ_LampLink_Provider_h */
