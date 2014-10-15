#ifndef _MySpareConfigurationService_Provider_h
#define _MySpareConfigurationService_Provider_h

#include <cimple/cimple.h>
#include "MySpareConfigurationService.h"

CIMPLE_NAMESPACE_BEGIN

class MySpareConfigurationService_Provider
{
public:

    typedef MySpareConfigurationService Class;

    MySpareConfigurationService_Provider();

    ~MySpareConfigurationService_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const MySpareConfigurationService* model,
        MySpareConfigurationService*& instance);

    Enum_Instances_Status enum_instances(
        const MySpareConfigurationService* model,
        Enum_Instances_Handler<MySpareConfigurationService>* handler);

    Create_Instance_Status create_instance(
        MySpareConfigurationService* instance);

    Delete_Instance_Status delete_instance(
        const MySpareConfigurationService* instance);

    Modify_Instance_Status modify_instance(
        const MySpareConfigurationService* model,
        const MySpareConfigurationService* instance);

    Invoke_Method_Status RequestStateChange(
        const MySpareConfigurationService* self,
        const Property<uint16>& RequestedState,
        CIM_ConcreteJob*& Job,
        const Property<Datetime>& TimeoutPeriod,
        Property<uint32>& return_value);

    Invoke_Method_Status StartService(
        const MySpareConfigurationService* self,
        Property<uint32>& return_value);

    Invoke_Method_Status StopService(
        const MySpareConfigurationService* self,
        Property<uint32>& return_value);

    Invoke_Method_Status AssignSpares(
        const MySpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StoragePool* InPool,
        const Array<CIM_StorageExtent*>& InExtents,
        const CIM_StorageRedundancySet* RedundancySet,
        Property<uint32>& return_value);

    Invoke_Method_Status UnassignSpares(
        const MySpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StoragePool* InPool,
        const Array<CIM_StorageExtent*>& InExtents,
        Property<uint32>& return_value);

    Invoke_Method_Status RebuildStorageExtent(
        const MySpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StorageExtent* Target,
        Property<uint32>& return_value);

    Invoke_Method_Status CheckParityConsistency(
        const MySpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StorageExtent* Target,
        Property<uint32>& return_value);

    Invoke_Method_Status RepairParity(
        const MySpareConfigurationService* self,
        CIM_ConcreteJob*& Job,
        const CIM_StorageExtent* Target,
        Property<uint32>& return_value);

    /*@END@*/
};

CIMPLE_NAMESPACE_END

#endif /* _MySpareConfigurationService_Provider_h */
