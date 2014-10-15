#ifndef _ComputerSystemDiskDrive_Provider_h
#define _ComputerSystemDiskDrive_Provider_h

#include <cimple/cimple.h>
#include "ComputerSystemDiskDrive.h"

CIMPLE_NAMESPACE_BEGIN

class ComputerSystemDiskDrive_Provider
{
public:

    typedef ComputerSystemDiskDrive Class;

    ComputerSystemDiskDrive_Provider();

    CIMPLE_HIDE ~ComputerSystemDiskDrive_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const ComputerSystemDiskDrive* model,
	ComputerSystemDiskDrive*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const ComputerSystemDiskDrive* model,
	Enum_Instances_Handler<ComputerSystemDiskDrive>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const ComputerSystemDiskDrive* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const ComputerSystemDiskDrive* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const ComputerSystemDiskDrive* instance);

    CIMPLE_HIDE static int proc(
	int operation, void* arg0, void* arg1, void* arg2, void* arg3);
};

CIMPLE_NAMESPACE_END

#endif /* _ComputerSystemDiskDrive_Provider_h */
