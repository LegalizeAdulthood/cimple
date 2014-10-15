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

Timer_Status ComputerSystemDiskDrive_Provider::timer(uint64& timeout_msec)
{
    return TIMER_CANCEL;
}

Get_Instance_Status ComputerSystemDiskDrive_Provider::get_instance(
    const ComputerSystemDiskDrive* model,
    ComputerSystemDiskDrive*& instance)
{
    return GET_INSTANCE_NOT_FOUND;
}

Enum_Instances_Status ComputerSystemDiskDrive_Provider::enum_instances(
    const ComputerSystemDiskDrive* model,
    Enum_Instances_Handler<ComputerSystemDiskDrive>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status ComputerSystemDiskDrive_Provider::create_instance(
    const ComputerSystemDiskDrive* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status ComputerSystemDiskDrive_Provider::delete_instance(
    const ComputerSystemDiskDrive* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status ComputerSystemDiskDrive_Provider::modify_instance(
    const ComputerSystemDiskDrive* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int ComputerSystemDiskDrive_Provider::proc(
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

    typedef ComputerSystemDiskDrive Class;
    typedef ComputerSystemDiskDrive_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
	operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
