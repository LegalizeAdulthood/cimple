#include "XYZ_Lamp_Provider.h"

CIMPLE_NAMESPACE_BEGIN

XYZ_Lamp_Provider::XYZ_Lamp_Provider()
{
}

XYZ_Lamp_Provider::~XYZ_Lamp_Provider()
{
}

Load_Status XYZ_Lamp_Provider::load()
{
    return LOAD_OK;
}

Unload_Status XYZ_Lamp_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status XYZ_Lamp_Provider::get_instance(
    const XYZ_Lamp* model,
    XYZ_Lamp*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status XYZ_Lamp_Provider::enum_instances(
    const XYZ_Lamp* model,
    Enum_Instances_Handler<XYZ_Lamp>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status XYZ_Lamp_Provider::create_instance(
    const XYZ_Lamp* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status XYZ_Lamp_Provider::delete_instance(
    const XYZ_Lamp* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status XYZ_Lamp_Provider::modify_instance(
    const XYZ_Lamp* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status XYZ_Lamp_Provider::foo(
    const XYZ_Lamp* self,
    const Property<String>& arg1,
    const Property<String>& arg2,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

int XYZ_Lamp_Provider::proc(
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

    typedef XYZ_Lamp Class;
    typedef XYZ_Lamp_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo") == 0)
    {
        typedef XYZ_Lamp_foo_method Method;
        Method* method = (Method*)arg2;
        return provider->foo(
            self,
            method->arg1,
            method->arg2,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/XYZ_Lamp/XYZ_Lamp_Provider.cpp,v 1.4 2007/03/07 20:25:29 mbrasher-public Exp $");
