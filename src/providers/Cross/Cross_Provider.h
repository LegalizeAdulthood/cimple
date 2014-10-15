#ifndef _Cross_Provider_h
#define _Cross_Provider_h

#include <cimple/cimple.h>
#include "Cross.h"

CIMPLE_NAMESPACE_BEGIN

class Cross_Provider
{
public:

    typedef Cross Class;

    Cross_Provider();

    ~Cross_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Cross* model,
        Cross*& instance);

    Enum_Instances_Status enum_instances(
        const Cross* model,
        Enum_Instances_Handler<Cross>* handler);

    Create_Instance_Status create_instance(
        Cross* instance);

    Delete_Instance_Status delete_instance(
        const Cross* instance);

    Modify_Instance_Status modify_instance(
        const Cross* model,
        const Cross* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const Cross* model,
        const String& role,
        Enum_References_Handler<Cross>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Cross_Provider_h */
