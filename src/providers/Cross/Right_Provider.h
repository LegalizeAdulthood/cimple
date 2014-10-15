#ifndef _Right_Provider_h
#define _Right_Provider_h

#include <cimple/cimple.h>
#include "Right.h"

CIMPLE_NAMESPACE_BEGIN

class Right_Provider
{
public:

    typedef Right Class;

    Right_Provider();

    ~Right_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Right* model,
        Right*& instance);

    Enum_Instances_Status enum_instances(
        const Right* model,
        Enum_Instances_Handler<Right>* handler);

    Create_Instance_Status create_instance(
        Right* instance);

    Delete_Instance_Status delete_instance(
        const Right* instance);

    Modify_Instance_Status modify_instance(
        const Right* model,
        const Right* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _Right_Provider_h */
