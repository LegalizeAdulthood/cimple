#ifndef _UnixUser_Provider_h
#define _UnixUser_Provider_h

#include <cimple/cimple.h>
#include "UnixUser.h"

CIMPLE_NAMESPACE_BEGIN

class UnixUser_Provider
{
public:

    typedef UnixUser Class;

    UnixUser_Provider();

    ~UnixUser_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const UnixUser* model,
	UnixUser*& instance);

    Enum_Instances_Status enum_instances(
	const UnixUser* model,
	Enum_Instances_Handler<UnixUser>* handler);

    Create_Instance_Status create_instance(
        UnixUser* instance);

    Delete_Instance_Status delete_instance(
	const UnixUser* instance);

    Modify_Instance_Status modify_instance(
        const UnixUser* model,
        const UnixUser* instance);
};

CIMPLE_NAMESPACE_END

#endif /* _UnixUser_Provider_h */
