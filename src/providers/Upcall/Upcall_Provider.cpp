#include "Upcall_Provider.h"
#include "CIM_ComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

/*****************************************************************************
    This provider is a demonstration of using an upcall to enumerate instances
    of an Class that is implemented external to our provider and using 
    information from the returned instances.

    Note that we include both a separate function to perform the enumeration
    as a demonstration and also build the enumeration directly into our
    enumerateInstances implementation to show that it is simple to directly
    implement the upcall and use the iterator to drive a loop to use
    the returned information. 
*****************************************************************************/

/*
    Upcall function to enumerate CIM_ComputerSystem. The return from this is
    the error code.  This function demonstrates getting an enumeration from
    an upcall and using the resulting instances
*/
static int _enum_CIM_ComputerSystem()
{
    CIM_ComputerSystem* model = CIM_ComputerSystem::create();

    // Define the instance enumerator

    Instance_Enumerator ie;

    // Call the enumerate function for CIM_ComputerSystem

    if (cimom::enum_instances("root/cimv2", model, ie) != 0)
        return -1;

    // Iterate the enumeration responses

    for (; ie; ie++)
    {
        // get next instance Ref from the iterator

        Ref<Instance> inst = ie();

        // Cast the Ref to a CIM_ComputerSystem instance

        CIM_ComputerSystem* ccs = cast<CIM_ComputerSystem*>(inst.ptr());

        //print(ccs);   
    }

    return 0;
}

// The following is the thread processor to repeatedly execute the
// _enum_CIM_ComputerSystem functions as part of internal testing.
// arg is a pointer to the provider object.

static void* _thread_proc(void* arg)
{
    // Get the provider context
    Upcall_Provider* that = (Upcall_Provider*)arg;

    // get the input variables
    uint32 repetition_count = that->_repetition_count;
    uint32 delay = that->_delay;

    // default for delay is 1 Second
    delay = (delay == 0)? Time::SEC : Time::MSEC * delay;

    // repetition_count = 0 means endless repetition. We set to
    // nonzero to assure loop runs.
    uint32 count_limit = (repetition_count != 0)? repetition_count: 1;

    while (that->_counter.get() && (count_limit > 0))
    {
        uint32 repcounter;
        printf("**_thread_proc():_enum_CIM_ComputerSystem() delay=%ums"
               " counter=%u count=%u\n",
               delay/1000, count_limit, ++repcounter);

        _enum_CIM_ComputerSystem();

        Time::sleep(delay);

        // Decrement counter if input was not zero
        if (repetition_count != 0)
            count_limit--;
    }
    printf("**_thread_proc():_enum_CIM_ComputerSystem() finished\n");
    return 0;
}

/* Local function to execute the stop thread. Separate because
   thread stopped for multiple reasons.
*/
bool _stopThread(Atomic_Counter& _counter, Thread& _thread)
{
    // Code to join the upcall execution loop terminating the
    // execution of theis repeated repeated upcall
    if (_counter.get())
    {
        // Signal other thread to exit.
        _counter.dec();
        void* value_ptr;
        Thread::join(_thread, value_ptr);
        return true;
    }
    return false;
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

    // test the enumerate of CIM_Computer system.
    _enum_CIM_ComputerSystem();

    return LOAD_OK;
}

Unload_Status Upcall_Provider::unload()
{
    printf("***** Upcall_Provider::unload()\n");

    // stop the test thread if it is running

    _stopThread(_counter, _thread);

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

    // This test will build our instances based on a property in the
    // computerSystem instances so we need to get instances of this class 
    // with an upcall.
    // 
    // We do this directly because it is very simple to use the iterator
    // from the upcall to drive the loop to build our instances.
    
    CIM_ComputerSystem* computer_system_model = CIM_ComputerSystem::create();

    // Define the computerSystem instance enumerator and initiate the
    // enumerate of this class. If there are no instances of the other
    // class we simply return OK.

    Instance_Enumerator ie;
 
    if (cimom::enum_instances("root/cimv2", computer_system_model, ie) != 0)
        return ENUM_INSTANCES_OK;

    // Create Upcall instances each with the Name property from each
    // of the corresponding CIM_ComputerSystem instances. Since we use
    // the iterator, the returned instances are destroyed as we go out of 
    // scope (they are Refs).

    int upcall_key = 1;

    for (; ie; ie++)
    {
        // Create Instance for the next iterator returned and set smart
        // pointer
        
        Ref<Instance> inst = ie();

        // Cast to a CIM_ComputerSystem instance

        CIM_ComputerSystem* ccs = cast<CIM_ComputerSystem*>(inst.ptr());

        // Create the Upcall instance and set the key.  In this case we
        // simple increment a counter to set the key.
        
        Upcall* upcall = Upcall::create(true);
        upcall->key.set(upcall_key++);

        // Get the property from the upcall instance and set in our
        // instance

        String name = ccs->Name.value;
        upcall->ComputerSystemName.set(name);
        printf("Generate instance for %s\n",(const char*)name.c_str());

        // Send the created instance to the server

        handler->handle(upcall);
    }

    return ENUM_INSTANCES_OK;
}

Create_Instance_Status Upcall_Provider::create_instance(
    Upcall* instance)
{
    return CREATE_INSTANCE_UNSUPPORTED;
}

Delete_Instance_Status Upcall_Provider::delete_instance(
    const Upcall* instance)
{
    return DELETE_INSTANCE_UNSUPPORTED;
}

Modify_Instance_Status Upcall_Provider::modify_instance(
    const Upcall* model,
    const Upcall* instance)
{
    return MODIFY_INSTANCE_UNSUPPORTED;
}

Invoke_Method_Status Upcall_Provider::StartTest(
    const Property<uint32>& count,
    const Property<uint32>& delay,
    Property<uint32>& return_value)
{   
    // The following was implemented to test repeated upcalls for enumeration
    // but has been disabled for normal operation.  If enabled, it creates
    // a thread that repeatedly executes the upcall until the provider is
    // unloaded.
    // 
    // Create thread to continually call _enum_CIM_ComputerSystem().
    // 
    return_value.null = false;

    if (count.null)
    {
        _repetition_count = 0;
    }
    else
        _repetition_count = count.value;

    _delay = delay.value;

    if (_counter.get() == 0)
    {
        _counter.inc();
        Thread::create_joinable(_thread, (Thread_Proc)_thread_proc, this);
        return_value.set(0);
    }
    else
        return_value.set(1);

    return INVOKE_METHOD_OK;
}

Invoke_Method_Status Upcall_Provider::StopTest(
    Property<uint32>& return_value)
{
    // Code to join the upcall execution loop terminating the
    // execution of repeated repeated upcall test
    
    return_value.null = false;

    // The _stopThread does not return until the thread is stopped.
    // Therefore large delay parameter times can cause delays in the response.
    
    if (_stopThread(_counter, _thread))
        return_value.set(0);
    else
        return_value.set(1);

    return INVOKE_METHOD_OK;
}

/*@END@*/

CIMPLE_NAMESPACE_END

