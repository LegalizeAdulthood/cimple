#ifndef _Upcall_Provider_h
#define _Upcall_Provider_h

#include <cimple/cimple.h>
#include "Upcall.h"

CIMPLE_NAMESPACE_BEGIN

class Upcall_Provider
{
public:

    typedef Upcall Class;

    Upcall_Provider();

    ~Upcall_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Upcall* model,
        Upcall*& instance);

    Enum_Instances_Status enum_instances(
        const Upcall* model,
        Enum_Instances_Handler<Upcall>* handler);

    Create_Instance_Status create_instance(
        const Upcall* instance);

    Delete_Instance_Status delete_instance(
        const Upcall* instance);

    Modify_Instance_Status modify_instance(
        const Upcall* instance);

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

    Thread thread;
    Atomic_Counter counter;
};

CIMPLE_NAMESPACE_END

#endif /* _Upcall_Provider_h */
