#ifndef _Hello_Provider_h
#define _Hello_Provider_h

#include <cimple/cimple.h>
#include "Hello.h"

CIMPLE_NAMESPACE_BEGIN

class Hello_Provider
{
public:

    typedef Hello Class;

    Hello_Provider();

    ~Hello_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const Hello* model,
        Hello*& instance);

    Enum_Instances_Status enum_instances(
        const Hello* model,
        Enum_Instances_Handler<Hello>* handler);

    Create_Instance_Status create_instance(
        Hello* instance);

    Delete_Instance_Status delete_instance(
        const Hello* instance);

    Modify_Instance_Status modify_instance(
        const Hello* model,
        const Hello* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _Hello_Provider_h */
