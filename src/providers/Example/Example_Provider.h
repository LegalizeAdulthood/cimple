#ifndef _Example_Provider_h
#define _Example_Provider_h

#include <cimple/cimple.h>
#include "Example.h"

CIMPLE_NAMESPACE_BEGIN

class Example_Provider
{
public:

    typedef Example Class;

    Example_Provider();

    ~Example_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const Example* model,
	Example*& instance);

    Enum_Instances_Status enum_instances(
	const Example* model,
	Enum_Instances_Handler<Example>* handler);

    Create_Instance_Status create_instance(
        Example* instance);

    Delete_Instance_Status delete_instance(
	const Example* instance);

    Modify_Instance_Status modify_instance(
        const Example* model,
        const Example* instance);

    Invoke_Method_Status foo0(
        const Example* self,
        Property<uint32>& return_value);

    Invoke_Method_Status foo1(
        const Example* self,
        const Property<real32>& x,
        const Property<uint32>& y,
        const Property<boolean>& z,
        Property<uint32>& return_value);

    Invoke_Method_Status foo2(
        const Example* self,
        const Property<String>& w,
        const Property<real32>& x,
        const Property<uint32>& y,
        const Property<boolean>& z,
        Property<uint32>& return_value);

    Invoke_Method_Status foo3(
        const Example* self,
        Property<String>& return_value);

    Invoke_Method_Status foo4(
        const Example* self,
        const Property<Array_real32>& x,
        Property<String>& return_value);

    Invoke_Method_Status foo5(
        const Example* self,
        const House* house,
        Property<String>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _Example_Provider_h */
