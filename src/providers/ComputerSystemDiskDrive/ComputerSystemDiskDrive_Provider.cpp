#include "ComputerSystemDiskDrive_Provider.h"

CIMPLE_NAMESPACE_BEGIN

ComputerSystemDiskDrive_Provider::ComputerSystemDiskDrive_Provider()
{
}

ComputerSystemDiskDrive_Provider::~ComputerSystemDiskDrive_Provider()
{
}

Load_Status ComputerSystemDiskDrive_Provider::load()
{
    return LOAD_OK;
}

Unload_Status ComputerSystemDiskDrive_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status ComputerSystemDiskDrive_Provider::get_instance(
    const ComputerSystemDiskDrive* model,
    ComputerSystemDiskDrive*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status ComputerSystemDiskDrive_Provider::enum_instances(
    const ComputerSystemDiskDrive* model,
    Enum_Instances_Handler<ComputerSystemDiskDrive>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status ComputerSystemDiskDrive_Provider::create_instance(
    ComputerSystemDiskDrive* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status ComputerSystemDiskDrive_Provider::delete_instance(
    const ComputerSystemDiskDrive* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status ComputerSystemDiskDrive_Provider::modify_instance(
    const ComputerSystemDiskDrive* model,
    const ComputerSystemDiskDrive* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Enum_Associator_Names_Status 
ComputerSystemDiskDrive_Provider::enum_associator_names(
    const Instance* instance,
    const String& result_class,
    const String& role,
    const String& result_role,
    Enum_Associator_Names_Handler<Instance>* handler)
{
    return ENUM_ASSOCIATOR_NAMES_UNSUPPORTED;
}

Enum_References_Status ComputerSystemDiskDrive_Provider::enum_references(
    const Instance* instance,
    const ComputerSystemDiskDrive* model,
    const String& role,
    Enum_References_Handler<ComputerSystemDiskDrive>* handler)
{
    return ENUM_REFERENCES_UNSUPPORTED;
}

Enum_Associators_Status ComputerSystemDiskDrive_Provider::enum_associators(
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
