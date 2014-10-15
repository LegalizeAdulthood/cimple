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
    print(self);
    print(Goal);

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

int CIM_StoragePool_Provider::proc(
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

    typedef CIM_StoragePool Class;
    typedef CIM_StoragePool_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "GetSupportedSizes") == 0)
    {
        typedef CIM_StoragePool_GetSupportedSizes_method Method;
        Method* method = (Method*)arg2;
        return provider->GetSupportedSizes(
            self,
            method->ElementType,
            method->Goal,
            method->Sizes,
            method->return_value);
    }
    if (strcasecmp(meth_name, "GetSupportedSizeRange") == 0)
    {
        typedef CIM_StoragePool_GetSupportedSizeRange_method Method;
        Method* method = (Method*)arg2;
        return provider->GetSupportedSizeRange(
            self,
            method->ElementType,
            method->Goal,
            method->MinimumVolumeSize,
            method->MaximumVolumeSize,
            method->VolumeSizeDivisor,
            method->return_value);
    }
    if (strcasecmp(meth_name, "GetAvailableExtents") == 0)
    {
        typedef CIM_StoragePool_GetAvailableExtents_method Method;
        Method* method = (Method*)arg2;
        return provider->GetAvailableExtents(
            self,
            method->Goal,
            method->AvailableExtents,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/CIM_StoragePool/CIM_StoragePool_Provider.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
