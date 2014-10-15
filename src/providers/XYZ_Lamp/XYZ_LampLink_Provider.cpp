#include "XYZ_LampLink_Provider.h"

CIMPLE_NAMESPACE_BEGIN

XYZ_LampLink_Provider::XYZ_LampLink_Provider()
{
}

XYZ_LampLink_Provider::~XYZ_LampLink_Provider()
{
}

Load_Status XYZ_LampLink_Provider::load()
{
    return LOAD_OK;
}

Unload_Status XYZ_LampLink_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status XYZ_LampLink_Provider::get_instance(
    const XYZ_LampLink* model,
    XYZ_LampLink*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status XYZ_LampLink_Provider::enum_instances(
    const XYZ_LampLink* model,
    Enum_Instances_Handler<XYZ_LampLink>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status XYZ_LampLink_Provider::create_instance(
    XYZ_LampLink* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status XYZ_LampLink_Provider::delete_instance(
    const XYZ_LampLink* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status XYZ_LampLink_Provider::modify_instance(
    const XYZ_LampLink* model,
    const XYZ_LampLink* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status XYZ_LampLink_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status XYZ_LampLink_Provider::enum_references(
    const Instance* instance,
    const XYZ_LampLink* model,
    const String& role,
    Enum_References_Handler<XYZ_LampLink>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status XYZ_LampLink_Provider::enum_associators(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associators_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATORS_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END

