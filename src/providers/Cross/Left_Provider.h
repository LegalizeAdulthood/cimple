#ifndef _Left_Provider_h
#define _Left_Provider_h

#include <cimple/cimple.h>
#include "Left.h"

CIMPLE_NAMESPACE_BEGIN

class Left_Provider
{
public:

    typedef Left Class;

    Left_Provider();

    ~Left_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Left* model,
        Left*& instance);

    Enum_Instances_Status enum_instances(
        const Left* model,
        Enum_Instances_Handler<Left>* handler);

    Create_Instance_Status create_instance(
        Left* instance);

    Delete_Instance_Status delete_instance(
        const Left* instance);

    Modify_Instance_Status modify_instance(
        const Left* model,
        const Left* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _Left_Provider_h */
