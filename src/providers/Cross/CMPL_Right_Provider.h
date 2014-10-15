#ifndef _CMPL_Right_Provider_h
#define _CMPL_Right_Provider_h

#include <cimple/cimple.h>
#include "CMPL_Right.h"

CIMPLE_NAMESPACE_BEGIN

class CMPL_Right_Provider
{
public:

    typedef CMPL_Right Class;

    CMPL_Right_Provider();

    ~CMPL_Right_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const CMPL_Right* model,
        CMPL_Right*& instance);

    Enum_Instances_Status enum_instances(
        const CMPL_Right* model,
        Enum_Instances_Handler<CMPL_Right>* handler);

    Create_Instance_Status create_instance(
        const CMPL_Right* instance);

    Delete_Instance_Status delete_instance(
        const CMPL_Right* instance);

    Modify_Instance_Status modify_instance(
        const CMPL_Right* instance);

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

#endif /* _CMPL_Right_Provider_h */
