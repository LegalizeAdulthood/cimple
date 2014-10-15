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

    CIMPLE_HIDE ~Example_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const Example* model,
	Example*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const Example* model,
	Enum_Instances_Handler<Example>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const Example* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const Example* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const Example* instance);

    CIMPLE_HIDE Invoke_Method_Status foo0(
        const Example* self,
        Property<uint32>& return_value);

    CIMPLE_HIDE Invoke_Method_Status foo1(
        const Example* self,
        const Property<real32>& x,
        const Property<uint32>& y,
        const Property<boolean>& z,
        Property<uint32>& return_value);

    CIMPLE_HIDE Invoke_Method_Status foo2(
        const Example* self,
        const Property<String>& w,
        const Property<real32>& x,
        const Property<uint32>& y,
        const Property<boolean>& z,
        Property<uint32>& return_value);

    CIMPLE_HIDE Invoke_Method_Status foo3(
        const Example* self,
        Property<String>& return_value);

    CIMPLE_HIDE Invoke_Method_Status foo4(
        const Example* self,
        const Property<Array_real32>& x,
        Property<String>& return_value);

    CIMPLE_HIDE Invoke_Method_Status foo5(
        const Example* self,
        const House* house,
        Property<String>& return_value);

    static CIMPLE_HIDE int proc(
	int operation, void* arg0, void* arg1, void* arg2, void* arg3);
};

CIMPLE_NAMESPACE_END

#endif /* _Example_Provider_h */
