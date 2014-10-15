#include "XYZ_Lamp_Provider.h"

CIMPLE_NAMESPACE_BEGIN

XYZ_Lamp_Provider::XYZ_Lamp_Provider()
{
}

XYZ_Lamp_Provider::~XYZ_Lamp_Provider()
{
}

Load_Status XYZ_Lamp_Provider::load()
{
    return LOAD_OK;
}

Unload_Status XYZ_Lamp_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status XYZ_Lamp_Provider::get_instance(
    const XYZ_Lamp* model,
    XYZ_Lamp*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status XYZ_Lamp_Provider::enum_instances(
    const XYZ_Lamp* model,
    Enum_Instances_Handler<XYZ_Lamp>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status XYZ_Lamp_Provider::create_instance(
    XYZ_Lamp* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status XYZ_Lamp_Provider::delete_instance(
    const XYZ_Lamp* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status XYZ_Lamp_Provider::modify_instance(
    const XYZ_Lamp* model,
    const XYZ_Lamp* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status XYZ_Lamp_Provider::foo(
    const XYZ_Lamp* self,
    const Property<String>& arg1,
    const Property<String>& arg2,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

