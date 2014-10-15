#include "CIM_ConcreteJob_Provider.h"

CIMPLE_NAMESPACE_BEGIN

CIM_ConcreteJob_Provider::CIM_ConcreteJob_Provider()
{
}

CIM_ConcreteJob_Provider::~CIM_ConcreteJob_Provider()
{
}

Load_Status CIM_ConcreteJob_Provider::load()
{
    return LOAD_OK;
}

Unload_Status CIM_ConcreteJob_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status CIM_ConcreteJob_Provider::get_instance(
    const CIM_ConcreteJob* model,
    CIM_ConcreteJob*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status CIM_ConcreteJob_Provider::enum_instances(
    const CIM_ConcreteJob* model,
    Enum_Instances_Handler<CIM_ConcreteJob>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status CIM_ConcreteJob_Provider::create_instance(
    CIM_ConcreteJob* instance)
{
    print(instance, true);

    instance->InstanceID.value = "2222";
    instance->InstanceID.null = false;

    print(instance, true);

    return CREATE_INSTANCE_OK;
}

Delete_Instance_Status CIM_ConcreteJob_Provider::delete_instance(
    const CIM_ConcreteJob* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status CIM_ConcreteJob_Provider::modify_instance(
    const CIM_ConcreteJob* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status CIM_ConcreteJob_Provider::KillJob(
    const CIM_ConcreteJob* self,
    const Property<boolean>& DeleteOnKill,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status CIM_ConcreteJob_Provider::RequestStateChange(
    const CIM_ConcreteJob* self,
    const Property<uint16>& RequestedState,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int CIM_ConcreteJob_Provider::proc(
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

    typedef CIM_ConcreteJob Class;
    typedef CIM_ConcreteJob_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "KillJob") == 0)
    {
        typedef CIM_ConcreteJob_KillJob_method Method;
        Method* method = (Method*)arg2;
        return provider->KillJob(
            self,
            method->DeleteOnKill,
            method->return_value);
    }
    if (strcasecmp(meth_name, "RequestStateChange") == 0)
    {
        typedef CIM_ConcreteJob_RequestStateChange_method Method;
        Method* method = (Method*)arg2;
        return provider->RequestStateChange(
            self,
            method->RequestedState,
            method->TimeoutPeriod,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
