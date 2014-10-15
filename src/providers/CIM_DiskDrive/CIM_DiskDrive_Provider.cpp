#include "CIM_DiskDrive_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CIM_DiskDrive_Provider::CIM_DiskDrive_Provider()
{
}

CIM_DiskDrive_Provider::~CIM_DiskDrive_Provider()
{
}

Load_Status CIM_DiskDrive_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CIM_DiskDrive_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CIM_DiskDrive_Provider::get_instance(
    const CIM_DiskDrive* model,
    CIM_DiskDrive*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CIM_DiskDrive_Provider::enum_instances(
    const CIM_DiskDrive* model,
    Enum_Instances_Handler<CIM_DiskDrive>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CIM_DiskDrive_Provider::create_instance(
    const CIM_DiskDrive* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status CIM_DiskDrive_Provider::delete_instance(
    const CIM_DiskDrive* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CIM_DiskDrive_Provider::modify_instance(
    const CIM_DiskDrive* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::RequestStateChange(
    const CIM_DiskDrive* self,
    const Property<uint16>& RequestedState,
    CIM_ConcreteJob* Job,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::SetPowerState(
    const CIM_DiskDrive* self,
    const Property<uint16>& PowerState,
    const Property<Datetime>& Time,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::Reset(
    const CIM_DiskDrive* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::EnableDevice(
    const CIM_DiskDrive* self,
    const Property<boolean>& Enabled,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::OnlineDevice(
    const CIM_DiskDrive* self,
    const Property<boolean>& Online,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::QuiesceDevice(
    const CIM_DiskDrive* self,
    const Property<boolean>& Quiesce,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::SaveProperties(
    const CIM_DiskDrive* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::RestoreProperties(
    const CIM_DiskDrive* self,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_DiskDrive_Provider::LockMedia(
    const CIM_DiskDrive* self,
    const Property<boolean>& Lock,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int CIM_DiskDrive_Provider::proc(
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

    typedef CIM_DiskDrive Class;
    typedef CIM_DiskDrive_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "RequestStateChange") == 0)
    {
        typedef CIM_DiskDrive_RequestStateChange_method Method;
        Method* method = (Method*)arg2;
        return provider->RequestStateChange(
            self,
            method->RequestedState,
            method->Job,
            method->TimeoutPeriod,
            method->return_value);
    }
    if (strcasecmp(meth_name, "SetPowerState") == 0)
    {
        typedef CIM_DiskDrive_SetPowerState_method Method;
        Method* method = (Method*)arg2;
        return provider->SetPowerState(
            self,
            method->PowerState,
            method->Time,
            method->return_value);
    }
    if (strcasecmp(meth_name, "Reset") == 0)
    {
        typedef CIM_DiskDrive_Reset_method Method;
        Method* method = (Method*)arg2;
        return provider->Reset(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "EnableDevice") == 0)
    {
        typedef CIM_DiskDrive_EnableDevice_method Method;
        Method* method = (Method*)arg2;
        return provider->EnableDevice(
            self,
            method->Enabled,
            method->return_value);
    }
    if (strcasecmp(meth_name, "OnlineDevice") == 0)
    {
        typedef CIM_DiskDrive_OnlineDevice_method Method;
        Method* method = (Method*)arg2;
        return provider->OnlineDevice(
            self,
            method->Online,
            method->return_value);
    }
    if (strcasecmp(meth_name, "QuiesceDevice") == 0)
    {
        typedef CIM_DiskDrive_QuiesceDevice_method Method;
        Method* method = (Method*)arg2;
        return provider->QuiesceDevice(
            self,
            method->Quiesce,
            method->return_value);
    }
    if (strcasecmp(meth_name, "SaveProperties") == 0)
    {
        typedef CIM_DiskDrive_SaveProperties_method Method;
        Method* method = (Method*)arg2;
        return provider->SaveProperties(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "RestoreProperties") == 0)
    {
        typedef CIM_DiskDrive_RestoreProperties_method Method;
        Method* method = (Method*)arg2;
        return provider->RestoreProperties(
            self,
            method->return_value);
    }
    if (strcasecmp(meth_name, "LockMedia") == 0)
    {
        typedef CIM_DiskDrive_LockMedia_method Method;
        Method* method = (Method*)arg2;
        return provider->LockMedia(
            self,
            method->Lock,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/CIM_DiskDrive/CIM_DiskDrive_Provider.cpp,v 1.3 2007/03/07 20:25:23 mbrasher-public Exp $");
