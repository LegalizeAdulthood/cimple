#ifndef _XYZ_Lamp_Provider_h
#define _XYZ_Lamp_Provider_h

#include <cimple/cimple.h>
#include "XYZ_Lamp.h"

CIMPLE_NAMESPACE_BEGIN

class XYZ_Lamp_Provider
{
public:

    typedef XYZ_Lamp Class;

    XYZ_Lamp_Provider();

    ~XYZ_Lamp_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const XYZ_Lamp* model,
	XYZ_Lamp*& instance);

    Enum_Instances_Status enum_instances(
	const XYZ_Lamp* model,
	Enum_Instances_Handler<XYZ_Lamp>* handler);

    Create_Instance_Status create_instance(
	const XYZ_Lamp* instance);

    Delete_Instance_Status delete_instance(
	const XYZ_Lamp* instance);

    Modify_Instance_Status modify_instance(
	const XYZ_Lamp* instance);

    Invoke_Method_Status foo(
        const XYZ_Lamp* self,
        const Property<String>& arg1,
        const Property<String>& arg2,
        Property<uint32>& return_value);

    static int proc(
	const Registration* registration,
	int operation, 
	void* arg0, 
	void* arg1, 
	void* arg2, 
	void* arg3,
	void* arg4,
	void* arg5,
	void* arg6,
	void* arg7);
};

CIMPLE_NAMESPACE_END

#endif /* _XYZ_Lamp_Provider_h */
