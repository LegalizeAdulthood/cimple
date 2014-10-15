#ifndef _SNIA_SpareConfigurationService_Provider_h
#define _SNIA_SpareConfigurationService_Provider_h

#include <cimple/cimple.h>
#include "SNIA_SpareConfigurationService.h"

CIMPLE_NAMESPACE_BEGIN

class SNIA_SpareConfigurationService_Provider
{
public:

    typedef SNIA_SpareConfigurationService Class;

    SNIA_SpareConfigurationService_Provider();

    ~SNIA_SpareConfigurationService_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const SNIA_SpareConfigurationService* model,
        SNIA_SpareConfigurationService*& instance);

    Enum_Instances_Status enum_instances(
        const SNIA_SpareConfigurationService* model,
        Enum_Instances_Handler<SNIA_SpareConfigurationService>* handler);

    Create_Instance_Status create_instance(
        const SNIA_SpareConfigurationService* instance);

    Delete_Instance_Status delete_instance(
        const SNIA_SpareConfigurationService* instance);

    Modify_Instance_Status modify_instance(
        const SNIA_SpareConfigurationService* model,
        const SNIA_SpareConfigurationService* instance);

    Invoke_Method_Status RequestStateChange(
        const SNIA_SpareConfigurationService* self,
        const Property<uint16>& RequestedState,
        CIM_ConcreteJob*& Job,
        const Property<Datetime>& TimeoutPeriod,
        Property<uint32>& return_value);

    Invoke_Method_Status StartService(
        const SNIA_SpareConfigurationService* self,
        Property<uint32>& return_value);

    Invoke_Method_Status StopService(
        const SNIA_SpareConfigurationService* self,
        Property<uint32>& return_value);

    Invoke_Method_Status AssignSpares(
        const SNIA_SpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StoragePool* InPool,
        const Array<CIM_StorageExtent*>& InExtents,
        const CIM_StorageRedundancySet* RedundancySet,
        Property<uint32>& return_value);

    Invoke_Method_Status UnassignSpares(
        const SNIA_SpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StoragePool* InPool,
        const Array<CIM_StorageExtent*>& InExtents,
        Property<uint32>& return_value);

    Invoke_Method_Status RebuildStorageExtent(
        const SNIA_SpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StorageExtent* Target,
        Property<uint32>& return_value);

    Invoke_Method_Status CheckParityConsistency(
        const SNIA_SpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StorageExtent* Target,
        Property<uint32>& return_value);

    Invoke_Method_Status RepairParity(
        const SNIA_SpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StorageExtent* Target,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _SNIA_SpareConfigurationService_Provider_h */
