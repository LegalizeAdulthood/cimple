#include "RefArray_Provider.h"
#include <syslog.h>

CIMPLE_NAMESPACE_BEGIN

RefArray_Provider::RefArray_Provider()
{
}

RefArray_Provider::~RefArray_Provider()
{
}

Load_Status RefArray_Provider::load()
{
    return LOAD_OK;
}

Unload_Status RefArray_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status RefArray_Provider::get_instance(
    const RefArray* model,
    RefArray*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status RefArray_Provider::enum_instances(
    const RefArray* model,
    Enum_Instances_Handler<RefArray>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status RefArray_Provider::create_instance(
    const RefArray* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status RefArray_Provider::delete_instance(
    const RefArray* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status RefArray_Provider::modify_instance(
    const RefArray* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status RefArray_Provider::SendRefArray(
    const RefArray* self,
    const RefArrayParam* arr1,
    RefArrayParam* arr2,
    Property<uint32>& return_value)
{
    syslog(LOG_ERR, "******************** SendRefArray()");

    return INVOKE_METHOD_OK;
}

int RefArray_Provider::proc(
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

    typedef RefArray Class;
    typedef RefArray_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "SendRefArray") == 0)
    {
        typedef RefArray_SendRefArray_method Method;
        Method* method = (Method*)arg2;
        return provider->SendRefArray(
            self,
            method->arr1,
            method->arr2,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/RefArray/RefArray_Provider.cpp,v 1.2 2007/03/07 20:25:27 mbrasher-public Exp $");
