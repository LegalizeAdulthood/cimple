#ifndef _BUG31_C_Provider_h
#define _BUG31_C_Provider_h

#include <cimple/cimple.h>
#include "BUG31_C.h"

CIMPLE_NAMESPACE_BEGIN

class BUG31_C_Provider
{
public:

    typedef BUG31_C Class;

    BUG31_C_Provider();

    ~BUG31_C_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const BUG31_C* model,
        BUG31_C*& instance);

    Enum_Instances_Status enum_instances(
        const BUG31_C* model,
        Enum_Instances_Handler<BUG31_C>* handler);

    Create_Instance_Status create_instance(
        BUG31_C* instance);

    Delete_Instance_Status delete_instance(
        const BUG31_C* instance);

    Modify_Instance_Status modify_instance(
        const BUG31_C* model,
        const BUG31_C* instance);

    Invoke_Method_Status meth(
        const BUG31_C* self,
        const BUG31_A* r,
        BUG31_A*& s,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _BUG31_C_Provider_h */
