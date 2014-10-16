#ifndef _BUG30_X_Provider_h
#define _BUG30_X_Provider_h

#include <cimple/cimple.h>
#include "BUG30_X.h"

CIMPLE_NAMESPACE_BEGIN

class BUG30_X_Provider
{
public:

    typedef BUG30_X Class;

    BUG30_X_Provider();

    ~BUG30_X_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const BUG30_X* model,
        BUG30_X*& instance);

    Enum_Instances_Status enum_instances(
        const BUG30_X* model,
        Enum_Instances_Handler<BUG30_X>* handler);

    Create_Instance_Status create_instance(
        const BUG30_X* instance);

    Delete_Instance_Status delete_instance(
        const BUG30_X* instance);

    Modify_Instance_Status modify_instance(
        const BUG30_X* instance);

    Invoke_Method_Status foo(
        const BUG30_X* self,
        const Array<BUG30_R*>& r1,
        Array<BUG30_R*>& r2,
        Property<uint32>& return_value);

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

#endif /* _BUG30_X_Provider_h */
