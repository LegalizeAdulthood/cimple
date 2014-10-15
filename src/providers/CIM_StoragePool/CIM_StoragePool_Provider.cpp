#include "CIM_StoragePool_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CIM_StoragePool_Provider::CIM_StoragePool_Provider()
{
}

CIM_StoragePool_Provider::~CIM_StoragePool_Provider()
{
}

Load_Status CIM_StoragePool_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CIM_StoragePool_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CIM_StoragePool_Provider::get_instance(
    const CIM_StoragePool* model,
    CIM_StoragePool*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CIM_StoragePool_Provider::enum_instances(
    const CIM_StoragePool* model,
    Enum_Instances_Handler<CIM_StoragePool>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CIM_StoragePool_Provider::create_instance(
    const CIM_StoragePool* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CIM_StoragePool_Provider::delete_instance(
    const CIM_StoragePool* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CIM_StoragePool_Provider::modify_instance(
    const CIM_StoragePool* model,
    const CIM_StoragePool* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status CIM_StoragePool_Provider::GetSupportedSizes(
    const CIM_StoragePool* self,
    const Property<uint16>& ElementType,
    const CIM_StorageSetting* Goal,
    Property<Array_uint64>& Sizes,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_StoragePool_Provider::GetSupportedSizeRange(
    const CIM_StoragePool* self,
    const Property<uint16>& ElementType,
    const CIM_StorageSetting* Goal,
    Property<uint64>& MinimumVolumeSize,
    Property<uint64>& MaximumVolumeSize,
    Property<uint64>& VolumeSizeDivisor,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_StoragePool_Provider::GetAvailableExtents(
    const CIM_StoragePool* self,
    const CIM_StorageSetting* Goal,
    Array<CIM_StorageExtent*>& AvailableExtents,
    Property<uint32>& return_value)
{
    print(self, true);
    print(Goal, true);

    for (size_t i = 0; i < AvailableExtents.size(); i++)
    {
        print(AvailableExtents[i], true);
    }

    CIM_StorageExtent* ext1 = CIM_StorageExtent::create();
    ext1->SystemCreationClassName.value = "CIM_ComputerSystem";
    ext1->SystemName.value = "localhost";
    ext1->CreationClassName.value = "CIM_StorageExtent";
    ext1->DeviceID.value = "DEVICE-01";

    CIM_StorageExtent* ext2 = CIM_StorageExtent::create();
    ext2->SystemCreationClassName.value = "CIM_ComputerSystem";
    ext2->SystemName.value = "localhost";
    ext2->CreationClassName.value = "CIM_StorageExtent";
    ext2->DeviceID.value = "DEVICE-02";

    AvailableExtents.clear();
    AvailableExtents.append(ext1);
    AvailableExtents.append(ext2);

    return_value.value = 100;
    return_value.null = false;

    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END

