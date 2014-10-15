#ifndef _CIM_StoragePool_Provider_h
#define _CIM_StoragePool_Provider_h

#include <cimple/cimple.h>
#include "CIM_StoragePool.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_StoragePool_Provider
{
public:

    typedef CIM_StoragePool Class;

    CIM_StoragePool_Provider();

    ~CIM_StoragePool_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const CIM_StoragePool* model,
        CIM_StoragePool*& instance);

    Enum_Instances_Status enum_instances(
        const CIM_StoragePool* model,
        Enum_Instances_Handler<CIM_StoragePool>* handler);

    Create_Instance_Status create_instance(
        const CIM_StoragePool* instance);

    Delete_Instance_Status delete_instance(
        const CIM_StoragePool* instance);

    Modify_Instance_Status modify_instance(
        const CIM_StoragePool* model,
        const CIM_StoragePool* instance);

    Invoke_Method_Status GetSupportedSizes(
        const CIM_StoragePool* self,
        const Property<uint16>& ElementType,
        const CIM_StorageSetting* Goal,
        Property<Array_uint64>& Sizes,
        Property<uint32>& return_value);

    Invoke_Method_Status GetSupportedSizeRange(
        const CIM_StoragePool* self,
        const Property<uint16>& ElementType,
        const CIM_StorageSetting* Goal,
        Property<uint64>& MinimumVolumeSize,
        Property<uint64>& MaximumVolumeSize,
        Property<uint64>& VolumeSizeDivisor,
        Property<uint32>& return_value);

    Invoke_Method_Status GetAvailableExtents(
        const CIM_StoragePool* self,
        const CIM_StorageSetting* Goal,
        Array<CIM_StorageExtent*>& AvailableExtents,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_StoragePool_Provider_h */
