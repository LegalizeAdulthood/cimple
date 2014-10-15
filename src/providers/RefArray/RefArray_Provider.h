#ifndef _RefArray_Provider_h
#define _RefArray_Provider_h

#include <cimple/cimple.h>
#include "RefArray.h"

CIMPLE_NAMESPACE_BEGIN

class RefArray_Provider
{
public:

    typedef RefArray Class;

    RefArray_Provider();

    ~RefArray_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const RefArray* model,
        RefArray*& instance);

    Enum_Instances_Status enum_instances(
        const RefArray* model,
        Enum_Instances_Handler<RefArray>* handler);

    Create_Instance_Status create_instance(
        const RefArray* instance);

    Delete_Instance_Status delete_instance(
        const RefArray* instance);

    Modify_Instance_Status modify_instance(
        const RefArray* instance);

    Invoke_Method_Status SendRefArray(
        const RefArray* self,
        const RefArrayParam* arr1,
        RefArrayParam* arr2,
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

#endif /* _RefArray_Provider_h */
