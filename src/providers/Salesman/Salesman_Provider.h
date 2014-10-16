#ifndef _Salesman_Provider_h
#define _Salesman_Provider_h

#include <cimple/cimple.h>
#include "Salesman.h"

CIMPLE_NAMESPACE_BEGIN

class Salesman_Provider
{
public:

    typedef Salesman Class;

    Salesman_Provider();

    ~Salesman_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Salesman* model,
        Salesman*& instance);

    Enum_Instances_Status enum_instances(
        const Salesman* model,
        Enum_Instances_Handler<Salesman>* handler);

    Create_Instance_Status create_instance(
        const Salesman* instance);

    Delete_Instance_Status delete_instance(
        const Salesman* instance);

    Modify_Instance_Status modify_instance(
        const Salesman* instance);

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

#endif /* _Salesman_Provider_h */
