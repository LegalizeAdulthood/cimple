#include "President_Provider.h"

CIMPLE_NAMESPACE_BEGIN

President_Provider::President_Provider()
{
}

President_Provider::~President_Provider()
{
}

Load_Status President_Provider::load()
{
    return LOAD_OK;
}

Unload_Status President_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status President_Provider::get_instance(
    const President* model,
    President*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status President_Provider::enum_instances(
    const President* model,
    Enum_Instances_Handler<President>* handler)
{
    {
        President* inst = President::create();
        inst->Number.value = 10;
        inst->First.value = "George";
        inst->Last.value = "Washington";
        handler->handle(inst);
    }

    {
        President* inst = President::create();
        inst->Number.value = 20;
        inst->First.value = "John";
        inst->Last.value = "Adams";
        handler->handle(inst);
    }

    {
        President* inst = President::create();
        inst->Number.value = 30;
        inst->First.value = "Thomas";
        inst->Last.value = "Jefferson";
        handler->handle(inst);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status President_Provider::create_instance(
    President* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status President_Provider::delete_instance(
    const President* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status President_Provider::modify_instance(
    const President* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int President_Provider::proc(
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

    typedef President Class;
    typedef President_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END
