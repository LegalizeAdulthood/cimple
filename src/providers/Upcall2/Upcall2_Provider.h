#ifndef _Upcall2_Provider_h
#define _Upcall2_Provider_h

#include <cimple/cimple.h>
#include "Upcall2.h"

CIMPLE_NAMESPACE_BEGIN

class Upcall2_Provider
{
public:

    typedef Upcall2 Class;

    Upcall2_Provider();

    ~Upcall2_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Upcall2* model,
        Upcall2*& instance);

    Enum_Instances_Status enum_instances(
        const Upcall2* model,
        Enum_Instances_Handler<Upcall2>* handler);

    Create_Instance_Status create_instance(
        const Upcall2* instance);

    Delete_Instance_Status delete_instance(
        const Upcall2* instance);

    Modify_Instance_Status modify_instance(
        const Upcall2* instance);

    Enum_Associator_Names_Status enum_associator_names(
        const Instance* instance,
        const String& result_class,
        const String& role,
        const String& result_role,
        Enum_Associator_Names_Handler<Instance>* handler);

    Enum_References_Status enum_references(
        const Instance* instance,
        const Upcall2* model,
        const String& role,
        Enum_References_Handler<Upcall2>* handler);

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

private:

    void _build_map(Instance_Map<Upcall2>& map);
};

CIMPLE_NAMESPACE_END

#endif /* _Upcall2_Provider_h */
