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

    CIMPLE_HIDE ~LinuxComputerSystem_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Get_Instance_Status get_instance(
	const LinuxComputerSystem* model,
	LinuxComputerSystem*& instance);

    CIMPLE_HIDE Enum_Instances_Status enum_instances(
	const LinuxComputerSystem* model,
	Enum_Instances_Handler<LinuxComputerSystem>* handler);

    CIMPLE_HIDE Create_Instance_Status create_instance(
	const LinuxComputerSystem* instance);

    CIMPLE_HIDE Delete_Instance_Status delete_instance(
	const LinuxComputerSystem* instance);

    CIMPLE_HIDE Modify_Instance_Status modify_instance(
	const LinuxComputerSystem* instance);

    CIMPLE_HIDE Invoke_Method_Status RequestStateChange(
        const LinuxComputerSystem* self,
        const Property<uint16>& RequestedState,
        CIM_ConcreteJob* Job,
        const Property<Datetime>& TimeoutPeriod,
        Property<uint32>& return_value);

    CIMPLE_HIDE Invoke_Method_Status SetPowerState(
        const LinuxComputerSystem* self,
        const Property<uint32>& PowerState,
        const Property<Datetime>& Time,
        Property<uint32>& return_value);

    CIMPLE_HIDE
    static int proc(
	int operation, void* arg0, void* arg1, void* arg2, void* arg3);
};

CIMPLE_NAMESPACE_END

#endif /* _LinuxComputerSystem_Provider_h */
