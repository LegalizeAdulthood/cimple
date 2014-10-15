#ifndef _CMPL_Cross_Provider_h
#define _CMPL_Cross_Provider_h

#include <cimple/cimple.h>
#include "CMPL_Cross.h"

CIMPLE_NAMESPACE_BEGIN

class CMPL_Cross_Provider
{
public:

    typedef CMPL_Cross Class;

    CMPL_Cross_Provider();

    ~CMPL_Cross_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const CMPL_Cross* model,
        CMPL_Cross*& instance);

    Enum_Instances_Status enum_instances(
        const CMPL_Cross* model,
        Enum_Instances_Handler<CMPL_Cross>* handler);

    Create_Instance_Status create_instance(
        CMPL_Cross* instance);

    Delete_Instance_Status delete_instance(
        const CMPL_Cross* instance);

    Modify_Instance_Status modify_instance(
        const CMPL_Cross* model,
        const CMPL_Cross* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const CMPL_Cross* model,
        const String& role,
        Enum_References_Handler<CMPL_Cross>* handler);

    Enum_Associators_Status enum_associators(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associators_Handler<Instance>* handler);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _CMPL_Cross_Provider_h */
