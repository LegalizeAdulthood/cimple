#ifndef _Methods_Provider_h
#define _Methods_Provider_h

#include <cimple/cimple.h>
#include "Methods.h"

CIMPLE_NAMESPACE_BEGIN

class Methods_Provider
{
public:

    typedef Methods Class;

    Methods_Provider();

    ~Methods_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Methods* model,
        Methods*& instance);

    Enum_Instances_Status enum_instances(
        const Methods* model,
        Enum_Instances_Handler<Methods>* handler);

    Create_Instance_Status create_instance(
        const Methods* instance);

    Delete_Instance_Status delete_instance(
        const Methods* instance);

    Modify_Instance_Status modify_instance(
        const Methods* instance);

    Invoke_Method_Status foo(
        const Methods* self,
        const Property<uint32>& arg1,
        const Property<String>& arg2,
        const Property<boolean>& arg3,
        Property<uint32>& arg4,
        Property<String>& arg5,
        Property<boolean>& arg6,
        Property<String>& return_value);

    Invoke_Method_Status foo2(
        const Methods* self,
        const Arg* arg1,
        Arg*& arg2,
        Property<String>& return_value);

    static int proc(
        const Registration* registration,
        int operation, void* arg0, void* arg1, void* arg2, void* arg3,
        void* arg4, void* arg5, void* arg6, void* arg7);
};

CIMPLE_NAMESPACE_END

#endif /* _Methods_Provider_h */
