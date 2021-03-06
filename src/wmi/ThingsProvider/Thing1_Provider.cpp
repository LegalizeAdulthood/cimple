// Generated by genprov 2.0.12
#include "Thing1_Provider.h"

CIMPLE_NAMESPACE_BEGIN

Thing1_Provider::Thing1_Provider()
{
}

Thing1_Provider::~Thing1_Provider()
{
}

Load_Status Thing1_Provider::load()
{
    return LOAD_OK;
}

Unload_Status Thing1_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status Thing1_Provider::get_instance(
    const Thing1* model,
    Thing1*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Thing1_Provider::enum_instances(
    const Thing1* model,
    Enum_Instances_Handler<Thing1>* handler)
{
    {
        Thing1* p = Thing1::create();
        p->id.set(1);
        p->name.set("Thing1 Number 1");
    
        handler->handle(p);
    }

    {
        Thing1* p = Thing1::create();
        p->id.set(2);
        p->name.set("Thing1 Number 2");
    
        handler->handle(p);
    }
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Thing1_Provider::create_instance(
    Thing1* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Thing1_Provider::delete_instance(
    const Thing1* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Thing1_Provider::modify_instance(
    const Thing1* model,
    const Thing1* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Thing1_Provider::foo(
    const Property<String>& arg,
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

/*@END@*/

CIMPLE_NAMESPACE_END
