#ifndef _PersonLink_Provider_h
#define _PersonLink_Provider_h

#include <cimple/cimple.h>
#include "PersonLink.h"

CIMPLE_NAMESPACE_BEGIN

class PersonLink_Provider
{
public:

    typedef PersonLink Class;

    PersonLink_Provider();

    ~PersonLink_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const PersonLink* model,
        PersonLink*& instance);

    Enum_Instances_Status enum_instances(
        const PersonLink* model,
        Enum_Instances_Handler<PersonLink>* handler);

    Create_Instance_Status create_instance(
        PersonLink* instance);

    Delete_Instance_Status delete_instance(
        const PersonLink* instance);

    Modify_Instance_Status modify_instance(
        const PersonLink* model,
        const PersonLink* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const PersonLink* model,
        const String& role,
        Enum_References_Handler<PersonLink>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/

private:

    Instance_Map<PersonLink> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _PersonLink_Provider_h */
