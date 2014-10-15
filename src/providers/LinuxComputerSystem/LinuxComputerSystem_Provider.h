#ifndef _LinuxComputerSystem_Provider_h
#define _LinuxComputerSystem_Provider_h

#include <cimple/cimple.h>
#include "LinuxComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

class LinuxComputerSystem_Provider
{
public:

    typedef LinuxComputerSystem Class;

    LinuxComputerSystem_Provider();

    ~LinuxComputerSystem_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const LinuxComputerSystem* model,
	LinuxComputerSystem*& instance);

    Enum_Instances_Status enum_instances(
	const LinuxComputerSystem* model,
	Enum_Instances_Handler<LinuxComputerSystem>* handler);

    Create_Instance_Status create_instance(
	const LinuxComputerSystem* instance);

    Delete_Instance_Status delete_instance(
	const LinuxComputerSystem* instance);

    Modify_Instance_Status modify_instance(
	const LinuxComputerSystem* instance);

    Invoke_Method_Status RequestStateChange(
        const LinuxComputerSystem* self,
        const Property<uint16>& RequestedState,
        CIM_ConcreteJob* Job,
        const Property<Datetime>& TimeoutPeriod,
        Property<uint32>& return_value);

    Invoke_Method_Status SetPowerState(
        const LinuxComputerSystem* self,
        const Property<uint32>& PowerState,
        const Property<Datetime>& Time,
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

#endif /* _LinuxComputerSystem_Provider_h */
