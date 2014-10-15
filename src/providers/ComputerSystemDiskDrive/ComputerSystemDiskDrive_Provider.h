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

    ~ComputerSystemDiskDrive_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const ComputerSystemDiskDrive* model,
	ComputerSystemDiskDrive*& instance);

    Enum_Instances_Status enum_instances(
	const ComputerSystemDiskDrive* model,
	Enum_Instances_Handler<ComputerSystemDiskDrive>* handler);

    Create_Instance_Status create_instance(
	const ComputerSystemDiskDrive* instance);

    Delete_Instance_Status delete_instance(
	const ComputerSystemDiskDrive* instance);

    Modify_Instance_Status modify_instance(
	const ComputerSystemDiskDrive* instance);

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

#endif /* _ComputerSystemDiskDrive_Provider_h */
