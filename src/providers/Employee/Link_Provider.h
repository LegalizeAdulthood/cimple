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
        Link* instance);

    Delete_Instance_Status delete_instance(
        const Link* instance);

    Modify_Instance_Status modify_instance(
        const Link* model,
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

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Link_Provider_h */
