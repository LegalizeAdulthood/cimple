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
    const XYZ_LampLink* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status XYZ_LampLink_Provider::delete_instance(
    const XYZ_LampLink* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status XYZ_LampLink_Provider::modify_instance(
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

int XYZ_LampLink_Provider::proc(
    const Registration* registration,
    int operation, 
    void* arg0, 
    void* arg1, 
    void* arg2, 
    void* arg3,
    void* arg4,
    void* arg5,
    void* arg6,
    void* arg7)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef XYZ_LampLink Class;
    typedef XYZ_LampLink_Provider Provider;
    return Association_Provider_Proc_T<Provider>::proc(registration, 
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
