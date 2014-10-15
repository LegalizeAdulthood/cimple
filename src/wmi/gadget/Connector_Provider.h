// Generated by genprov 1.2.5
#ifndef _Connector_Provider_h
#define _Connector_Provider_h

#include <cimple/cimple.h>
#include "Connector.h"

CIMPLE_NAMESPACE_BEGIN

class Connector_Provider
{
public:

    typedef Connector Class;

    Connector_Provider();

    ~Connector_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Connector* model,
        Connector*& instance);

    Enum_Instances_Status enum_instances(
        const Connector* model,
        Enum_Instances_Handler<Connector>* handler);

    Create_Instance_Status create_instance(
        Connector* instance);

    Delete_Instance_Status delete_instance(
        const Connector* instance);

    Modify_Instance_Status modify_instance(
        const Connector* model,
        const Connector* instance);

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
        const Connector* model,
        const String& role,
        Enum_References_Handler<Connector>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Connector_Provider_h */
