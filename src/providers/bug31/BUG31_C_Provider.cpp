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
    const BUG31_C* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status BUG31_C_Provider::delete_instance(
    const BUG31_C* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status BUG31_C_Provider::modify_instance(
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
    printf("==== BUG31_C_Provider::meth()\n");

    // Test is_a<> operator.

    if (is_a<BUG31_B>(r))
    {
        BUG31_B* b = (BUG31_B*)r;
        print(b);
    }

    // Test cast<> operator.

    BUG31_B* b = cast<BUG31_B*>(r);

    if (b)
        print(b);

    print(r);


    CIMPLE_ASSERT(s == 0);

    s = cast<BUG31_A*>(clone(r));

    CIMPLE_ASSERT(s != 0);

    print(s);

    return_value.null = false;
    return_value.value = 12345;

    return INVOKE_METHOD_OK;
}

int BUG31_C_Provider::proc(
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

    typedef BUG31_C Class;
    typedef BUG31_C_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "meth") == 0)
    {
        typedef BUG31_C_meth_method Method;
        Method* method = (Method*)arg2;
        return provider->meth(
            self,
            method->r,
            method->s,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/bug31/BUG31_C_Provider.cpp,v 1.2 2007/03/07 20:25:30 mbrasher-public Exp $");
