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

    CIMPLE_HIDE ~ThingLink_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
        const ThingLink* model,
        ThingLink*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
        const ThingLink* model,
        Enum_Instances_Handler<ThingLink>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
        const ThingLink* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
        const ThingLink* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
        const ThingLink* instance);

    CIMPLE_HIDE Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    CIMPLE_HIDE Enum_References_Status enum_references(
        const Instance* instance,
        const ThingLink* model,
        const String& role,
        Enum_References_Handler<ThingLink>* handler);

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

private:

    Instance_Map<ThingLink> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _ThingLink_Provider_h */
