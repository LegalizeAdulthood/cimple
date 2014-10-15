#include "BUG31_C_Provider.h"
#include "BUG31_B.h"

CIMPLE_NAMESPACE_BEGIN

BUG31_C_Provider::BUG31_C_Provider()
{
}

BUG31_C_Provider::~BUG31_C_Provider()
{
}

Load_Status BUG31_C_Provider::load()
{
    return LOAD_OK;
}

Unload_Status BUG31_C_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status BUG31_C_Provider::get_instance(
    const BUG31_C* model,
    BUG31_C*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status BUG31_C_Provider::enum_instances(
    const BUG31_C* model,
    Enum_Instances_Handler<BUG31_C>* handler)
{
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status BUG31_C_Provider::create_instance(
    BUG31_C* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status BUG31_C_Provider::delete_instance(
    const BUG31_C* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status BUG31_C_Provider::modify_instance(
    const BUG31_C* model,
    const BUG31_C* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status BUG31_C_Provider::meth(
    const BUG31_C* self,
    const BUG31_A* r,
    BUG31_A*& s,
    Property<uint32>& return_value)
{
    // printf("==== BUG31_C_Provider::meth()\n");

    // Test is_a<> operator.

    if (is_a<BUG31_B>(r))
    {
        BUG31_B* b = (BUG31_B*)r;
        // print(b);
    }

    // Test cast<> operator.

    BUG31_B* b = cast<BUG31_B*>(r);

    if (b)
    {
        // print(b);
    }

    // print(r);


    CIMPLE_ASSERT(s == 0);

    s = cast<BUG31_A*>(clone(r));

    CIMPLE_ASSERT(s != 0);

    // print(s);

    return_value.null = false;
    return_value.value = 12345;

    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END

