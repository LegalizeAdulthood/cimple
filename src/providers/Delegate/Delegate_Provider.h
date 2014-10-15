#ifndef _Delegate_Provider_h
#define _Delegate_Provider_h

#include <cimple/cimple.h>
#include "Delegate.h"

CIMPLE_NAMESPACE_BEGIN

class Delegate_Provider
{
public:

    typedef Delegate Class;

    Delegate_Provider();

    ~Delegate_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Delegate* model,
        Delegate*& instance);

    Enum_Instances_Status enum_instances(
        const Delegate* model,
        Enum_Instances_Handler<Delegate>* handler);

    Create_Instance_Status create_instance(
        Delegate* instance);

    Delete_Instance_Status delete_instance(
        const Delegate* instance);

    Modify_Instance_Status modify_instance(
        const Delegate* model,
        const Delegate* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _Delegate_Provider_h */
