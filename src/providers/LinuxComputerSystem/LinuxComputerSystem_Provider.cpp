#include "LinuxComputerSystem_Provider.h"

CIMPLE_NAMESPACE_BEGIN

LinuxComputerSystem_Provider::LinuxComputerSystem_Provider()
{
}

LinuxComputerSystem_Provider::~LinuxComputerSystem_Provider()
{
}

Load_Status LinuxComputerSystem_Provider::load()
{
    return LOAD_OK;
}

Unload_Status LinuxComputerSystem_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status LinuxComputerSystem_Provider::get_instance(
    const LinuxComputerSystem* model,
    LinuxComputerSystem*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status LinuxComputerSystem_Provider::enum_instances(
    const LinuxComputerSystem* model,
    Enum_Instances_Handler<LinuxComputerSystem>* handler)
{
    LinuxComputerSystem* inst = LinuxComputerSystem::create();
    inst->Name.value = "monday";
    inst->CreationClassName.value = "LinuxComputerSystem";
    handler->handle(inst);

    inst = LinuxComputerSystem::create();
    inst->Name.value = "tuesday";
    inst->CreationClassName.value = "LinuxComputerSystem";
    handler->handle(inst);

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status LinuxComputerSystem_Provider::create_instance(
    const LinuxComputerSystem* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status LinuxComputerSystem_Provider::delete_instance(
    const LinuxComputerSystem* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status LinuxComputerSystem_Provider::modify_instance(
    const LinuxComputerSystem* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status LinuxComputerSystem_Provider::RequestStateChange(
    const LinuxComputerSystem* self,
    const Property<uint16>& RequestedState,
    CIM_ConcreteJob* Job,
    const Property<Datetime>& TimeoutPeriod,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

Invoke_Method_Status LinuxComputerSystem_Provider::SetPowerState(
    const LinuxComputerSystem* self,
    const Property<uint32>& PowerState,
    const Property<Datetime>& Time,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int LinuxComputerSystem_Provider::proc(
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

    typedef LinuxComputerSystem Class;
    typedef LinuxComputerSystem_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "RequestStateChange") == 0)
    {
        typedef LinuxComputerSystem_RequestStateChange_method Method;
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
        typedef LinuxComputerSystem_SetPowerState_method Method;
        Method* method = (Method*)arg2;
        return provider->SetPowerState(
            self,
            method->PowerState,
            method->Time,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/LinuxComputerSystem/LinuxComputerSystem_Provider.cpp,v 1.20 2007/03/07 20:25:25 mbrasher-public Exp $");
