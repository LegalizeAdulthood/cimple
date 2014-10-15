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
        RefArray* instance);

    Delete_Instance_Status delete_instance(
        const RefArray* instance);

    Modify_Instance_Status modify_instance(
        const RefArray* model,
        const RefArray* instance);

    Invoke_Method_Status SendRefArray(
        const RefArray* self,
        const Property< Array<RefArrayParam*> >& arr1,
        Property< Array<RefArrayParam*> >& arr2,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _RefArray_Provider_h */
