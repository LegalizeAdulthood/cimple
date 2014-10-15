#ifndef _President_Provider_h
#define _President_Provider_h

#include <cimple/cimple.h>
#include "President.h"

CIMPLE_NAMESPACE_BEGIN

class President_Provider
{
public:

    typedef President Class;

    President_Provider();

    ~President_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const President* model,
        President*& instance);

    Enum_Instances_Status enum_instances(
        const President* model,
        Enum_Instances_Handler<President>* handler);

    Create_Instance_Status create_instance(
        President* instance);

    Delete_Instance_Status delete_instance(
        const President* instance);

    Modify_Instance_Status modify_instance(
        const President* model,
        const President* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _President_Provider_h */
