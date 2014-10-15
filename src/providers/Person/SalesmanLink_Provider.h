#ifndef _SalesmanLink_Provider_h
#define _SalesmanLink_Provider_h

#include <cimple/cimple.h>
#include "SalesmanLink.h"

CIMPLE_NAMESPACE_BEGIN

class SalesmanLink_Provider
{
public:

    typedef SalesmanLink Class;

    SalesmanLink_Provider();

    ~SalesmanLink_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const SalesmanLink* model,
        SalesmanLink*& instance);

    Enum_Instances_Status enum_instances(
        const SalesmanLink* model,
        Enum_Instances_Handler<SalesmanLink>* handler);

    Create_Instance_Status create_instance(
        SalesmanLink* instance);

    Delete_Instance_Status delete_instance(
        const SalesmanLink* instance);

    Modify_Instance_Status modify_instance(
        const SalesmanLink* model,
        const SalesmanLink* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const SalesmanLink* model,
        const String& role,
        Enum_References_Handler<SalesmanLink>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _SalesmanLink_Provider_h */
