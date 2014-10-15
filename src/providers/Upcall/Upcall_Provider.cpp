#include "Upcall_Provider.h"
#include "CIM_ComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

static int _enum_CIM_ComputerSystem()
{
    CIM_ComputerSystem* model = CIM_ComputerSystem::create();

    Instance_Enumerator ie;

    if (cimom::enum_instances("root/cimv2", model, ie) != 0)
        return -1;

    for (; ie; ie++)
    {
        Ref<Instance> inst = ie();
        print(inst.ptr());
    }

    return 0;
}

static void* _thread_proc(void* arg)
{
    Upcall_Provider* that = (Upcall_Provider*)arg;

    while (that->counter.get())
    {
        printf("*** _thread_proc(): _enum_CIM_ComputerSystem()\n");
        _enum_CIM_ComputerSystem();
        Time::sleep(Time::SEC);
    }

    return 0;
}

Upcall_Provider::Upcall_Provider()
{
}

Upcall_Provider::~Upcall_Provider()
{
}

Load_Status Upcall_Provider::load()
{
    printf("***** Upcall_Provider::load()\n");

    //cimom::allow_unload(false);

    _enum_CIM_ComputerSystem();

#if 0
    // Create thread to continually call _enum_CIM_ComputerSystem().
    counter.inc();
    Thread::create_joinable(thread, (Thread_Proc)_thread_proc, this);
#endif

    return LOAD_OK;
}

Unload_Status Upcall_Provider::unload()
{
    printf("***** Upcall_Provider::unload()\n");

#if 0
    if (counter.get())
    {
        // Signal other thread to exit.
        counter.dec();
        void* value_ptr;
        Thread::join(thread, value_ptr);
    }
#endif

    return UNLOAD_OK;
}

Get_Instance_Status Upcall_Provider::get_instance(
    const Upcall* model,
    Upcall*& instance)
{
    return GET_INSTANCE_UNSUPPORTED;
}

Enum_Instances_Status Upcall_Provider::enum_instances(
    const Upcall* model,
    Enum_Instances_Handler<Upcall>* handler)
{
    printf("***** Upcall_Provider::enum_instances()\n");

    _enum_CIM_ComputerSystem();
    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Upcall_Provider::create_instance(
    const Upcall* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Upcall_Provider::delete_instance(
    const Upcall* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Upcall_Provider::modify_instance(
    const Upcall* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

int Upcall_Provider::proc(
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

    typedef Upcall Class;
    typedef Upcall_Provider Provider;
    return Provider_Proc_T<Provider>::proc(registration,
        operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Upcall/Upcall_Provider.cpp,v 1.6 2007/03/07 20:25:28 mbrasher-public Exp $");
