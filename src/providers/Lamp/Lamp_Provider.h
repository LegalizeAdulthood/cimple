#ifndef _Lamp_Provider_h
#define _Lamp_Provider_h

#include <cimple/cimple.h>
#include "Lamp.h"

CIMPLE_NAMESPACE_BEGIN

class Lamp_Provider
{
public:

    typedef Lamp Class;

    Lamp_Provider();

    ~Lamp_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Lamp* model,
	Lamp*& instance);

    Enum_Instances_Status enum_instances(
	const Lamp* model,
	Enum_Instances_Handler<Lamp>* handler);

    Create_Instance_Status create_instance(
        Lamp* instance);

    Delete_Instance_Status delete_instance(
	const Lamp* instance);

    Modify_Instance_Status modify_instance(
        const Lamp* model,
        const Lamp* instance);

    Invoke_Method_Status foo(
        const Lamp* self,
        const Property<String>& arg1,
        const Property<String>& arg2,
        Property<uint32>& return_value);

private:

    Instance_Map<Lamp> _map;
};

CIMPLE_NAMESPACE_END

#endif /* _Lamp_Provider_h */
