#include "BUG30_X_Provider.h"

CIMPLE_NAMESPACE_BEGIN

static BUG30_R* _create_R(uint32 key)
{
    BUG30_R* r = BUG30_R::create();
    r->key.value = key;
    r->key.null = false;
    return r;
}

BUG30_X_Provider::BUG30_X_Provider()
{
}

BUG30_X_Provider::~BUG30_X_Provider()
{
}

Load_Status BUG30_X_Provider::load()
{
    return LOAD_OK;
}

Unload_Status BUG30_X_Provider::unload()
{
    return UNLOAD_OK;
}

Get_Instance_Status BUG30_X_Provider::get_instance(
    const BUG30_X* model,
    BUG30_X*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status BUG30_X_Provider::enum_instances(
    const BUG30_X* model,
    Enum_Instances_Handler<BUG30_X>* handler)
{
#if 0
    BUG30_X_foo_method* foo = BUG30_X_foo_method::create();

    foo->r1.append(_create_R(1000));
    foo->r1.append(_create_R(2000));
    foo->r1.append(_create_R(3000));

    foo->r2.append(_create_R(100));
    foo->r2.append(_create_R(200));

    print(foo);
#endif

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status BUG30_X_Provider::create_instance(
    const BUG30_X* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status BUG30_X_Provider::delete_instance(
    const BUG30_X* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status BUG30_X_Provider::modify_instance(
    const BUG30_X* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status BUG30_X_Provider::foo(
    const BUG30_X* self,
    const Array<BUG30_R*>& r1,
    Array<BUG30_R*>& r2,
    Property<uint32>& return_value)
{
    r2.clear();

    for (size_t i = 0; i < r1.size(); i++)
    {
        const BUG30_R* r = r1[i];


        if (r)
        {
            print(r);

            BUG30_R* tmp = r->clone();
#if 0
            tmp->__name_space = "root/xyz";
#endif
            r2.append(tmp);
        }
        else
            r2.append(0);
    }

    return_value.value = 1234;
    return_value.null = false;

    return INVOKE_METHOD_OK;
}

int BUG30_X_Provider::proc(
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

    typedef BUG30_X Class;
    typedef BUG30_X_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Provider_Proc_T<Provider>::proc(registration,
            operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "foo") == 0)
    {
        typedef BUG30_X_foo_method Method;
        Method* method = (Method*)arg2;
        return provider->foo(
            self,
            method->r1,
            method->r2,
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/bug30/BUG30_X_Provider.cpp,v 1.3 2007/03/07 20:25:29 mbrasher-public Exp $");
