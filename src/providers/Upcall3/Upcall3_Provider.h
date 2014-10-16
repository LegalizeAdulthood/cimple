#ifndef _Upcall3_Provider_h
#define _Upcall3_Provider_h

#include <cimple/cimple.h>
#include "Upcall3.h"

CIMPLE_NAMESPACE_BEGIN

class Upcall3_Provider
{
public:

    typedef Upcall3 Class;

    Upcall3_Provider();

    ~Upcall3_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Upcall3* model,
        Upcall3*& instance);

    Enum_Instances_Status enum_instances(
        const Upcall3* model,
        Enum_Instances_Handler<Upcall3>* handler);

    Create_Instance_Status create_instance(
        const Upcall3* instance);

    Delete_Instance_Status delete_instance(
        const Upcall3* instance);

    Modify_Instance_Status modify_instance(
        const Upcall3* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const Upcall3* model,
        const String& role,
        Enum_References_Handler<Upcall3>* handler);

    static int proc(
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
};

CIMPLE_NAMESPACE_END

#endif /* _Upcall3_Provider_h */
