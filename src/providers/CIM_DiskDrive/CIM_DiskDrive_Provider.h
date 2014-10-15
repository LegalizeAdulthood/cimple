#ifndef _CIM_DiskDrive_Provider_h
#define _CIM_DiskDrive_Provider_h

#include <cimple/cimple.h>
#include "CIM_DiskDrive.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_DiskDrive_Provider
{
public:

    typedef CIM_DiskDrive Class;

    CIM_DiskDrive_Provider();

    ~CIM_DiskDrive_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
	const CIM_DiskDrive* model,
	CIM_DiskDrive*& instance);

    Enum_Instances_Status enum_instances(
	const CIM_DiskDrive* model,
	Enum_Instances_Handler<CIM_DiskDrive>* handler);

    Create_Instance_Status create_instance(
        CIM_DiskDrive* instance);

    Delete_Instance_Status delete_instance(
	const CIM_DiskDrive* instance);

    Modify_Instance_Status modify_instance(
        const CIM_DiskDrive* model,
        const CIM_DiskDrive* instance);

    Invoke_Method_Status RequestStateChange(
        const CIM_DiskDrive* self,
        const Property<uint16>& RequestedState,
        CIM_ConcreteJob*& Job,
        const Property<Datetime>& TimeoutPeriod,
        Property<uint32>& return_value);

    Invoke_Method_Status SetPowerState(
        const CIM_DiskDrive* self,
        const Property<uint16>& PowerState,
        const Property<Datetime>& Time,
        Property<uint32>& return_value);

    Invoke_Method_Status Reset(
        const CIM_DiskDrive* self,
        Property<uint32>& return_value);

    Invoke_Method_Status EnableDevice(
        const CIM_DiskDrive* self,
        const Property<boolean>& Enabled,
        Property<uint32>& return_value);

    Invoke_Method_Status OnlineDevice(
        const CIM_DiskDrive* self,
        const Property<boolean>& Online,
        Property<uint32>& return_value);

    Invoke_Method_Status QuiesceDevice(
        const CIM_DiskDrive* self,
        const Property<boolean>& Quiesce,
        Property<uint32>& return_value);

    Invoke_Method_Status SaveProperties(
        const CIM_DiskDrive* self,
        Property<uint32>& return_value);

    Invoke_Method_Status RestoreProperties(
        const CIM_DiskDrive* self,
        Property<uint32>& return_value);

    Invoke_Method_Status LockMedia(
        const CIM_DiskDrive* self,
        const Property<boolean>& Lock,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_DiskDrive_Provider_h */
