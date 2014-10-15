#ifndef _Fan_Provider_h
#define _Fan_Provider_h

#include <cimple/cimple.h>
#include "Fan.h"

CIMPLE_NAMESPACE_BEGIN

class Fan_Provider
{
public:

    typedef Fan Class;

    Fan_Provider();

    ~Fan_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Fan* model,
	Fan*& instance);

    Enum_Instances_Status enum_instances(
	const Fan* model,
	Enum_Instances_Handler<Fan>* handler);

    Create_Instance_Status create_instance(
        Fan* instance);

    Delete_Instance_Status delete_instance(
	const Fan* inst);

    Modify_Instance_Status modify_instance(
        const Fan* model,
        const Fan* instance);

    Invoke_Method_Status SetSpeed(
        const Fan* self,
        const Property<uint64>& DesiredSpeed,
        Property<uint32>& return_value);

private:

    Instance_Map<Fan> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Fan_Provider_h */
