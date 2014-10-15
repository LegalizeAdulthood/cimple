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
        Methods* instance);

    Delete_Instance_Status delete_instance(
        const Methods* instance);

    Modify_Instance_Status modify_instance(
        const Methods* model,
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
        const Argument* arg1,
        Argument*& arg2,
        Property<String>& return_value);

    Invoke_Method_Status foo3(
        Property<String>& return_value);

    Invoke_Method_Status foo4(
        const Methods* self,
        const Property<Array_String>& arr1,
        Property<Array_String>& arr2,
        Property<uint32>& return_value);

    Invoke_Method_Status foo5(
        const Methods* self,
        const Property<uint32>& in_arg,
        Property<uint32>& in_out_arg,
        Property<uint32>& out_arg,
        Property<uint32>& return_value);

    Invoke_Method_Status junk(
        const Methods* self,
        const Property<uint32>& x,
        const Property<uint32>& y,
        Property<uint32>& return_value);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _Methods_Provider_h */
