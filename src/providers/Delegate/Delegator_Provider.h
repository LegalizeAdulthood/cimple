#ifndef _Delegator_Provider_h
#define _Delegator_Provider_h

#include <cimple/cimple.h>
#include "Delegator.h"

CIMPLE_NAMESPACE_BEGIN

class Delegator_Provider
{
public:

    typedef Delegator Class;

    Delegator_Provider();

    ~Delegator_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Delegator* model,
        Delegator*& instance);

    Enum_Instances_Status enum_instances(
        const Delegator* model,
        Enum_Instances_Handler<Delegator>* handler);

    Create_Instance_Status create_instance(
        Delegator* instance);

    Delete_Instance_Status delete_instance(
        const Delegator* instance);

    Modify_Instance_Status modify_instance(
        const Delegator* model,
        const Delegator* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _Delegator_Provider_h */
