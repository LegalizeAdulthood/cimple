#ifndef _ThingLink_Provider_h
#define _ThingLink_Provider_h

#include <cimple/cimple.h>
#include "ThingLink.h"

CIMPLE_NAMESPACE_BEGIN

class ThingLink_Provider
{
public:

    typedef ThingLink Class;

    ThingLink_Provider();

    ~ThingLink_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const ThingLink* model,
	ThingLink*& instance);

    Enum_Instances_Status enum_instances(
	const ThingLink* model,
	Enum_Instances_Handler<ThingLink>* handler);

    Create_Instance_Status create_instance(
        ThingLink* instance);

    Delete_Instance_Status delete_instance(
	const ThingLink* instance);

    Modify_Instance_Status modify_instance(
        const ThingLink* model,
        const ThingLink* instance);

    Enum_Associator_Names_Status enum_associator_names(
	const Instance* instance,
	const String& result_class,
	const String& role,
	const String& result_role,
	Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
	const Instance* instance,
	const ThingLink* model,
	const String& role,
	Enum_References_Handler<ThingLink>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/

private:

    Instance_Map<ThingLink> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _ThingLink_Provider_h */
