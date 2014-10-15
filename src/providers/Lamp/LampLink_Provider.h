#ifndef _LampLink_Provider_h
#define _LampLink_Provider_h

#include <cimple/cimple.h>
#include "LampLink.h"

CIMPLE_NAMESPACE_BEGIN

class LampLink_Provider
{
public:

    typedef LampLink Class;

    LampLink_Provider();

    ~LampLink_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const LampLink* model,
	LampLink*& instance);

    Enum_Instances_Status enum_instances(
	const LampLink* model,
	Enum_Instances_Handler<LampLink>* handler);

    Create_Instance_Status create_instance(
        LampLink* instance);

    Delete_Instance_Status delete_instance(
	const LampLink* instance);

    Modify_Instance_Status modify_instance(
        const LampLink* model,
        const LampLink* instance);

    Enum_Associator_Names_Status enum_associator_names(
	const Instance* instance,
	const String& result_class,
	const String& role,
	const String& result_role,
	Enum_Associator_Names_Handler<Instance>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    Enum_References_Status enum_references(
	const Instance* instance,
	const LampLink* model,
	const String& role,
	Enum_References_Handler<LampLink>* handler);
};

CIMPLE_NAMESPACE_END

#endif /* _LampLink_Provider_h */
