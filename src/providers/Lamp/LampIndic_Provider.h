#ifndef _LampIndic_Provider_h
#define _LampIndic_Provider_h

#include <cimple/cimple.h>
#include "LampIndic.h"
#include <cimple/Mutex.h>
#include <cimple/Thread.h>
#include <cimple/Atomic_Counter.h>

CIMPLE_NAMESPACE_BEGIN

class LampIndic_Provider
{
public:

    typedef LampIndic Class;

    LampIndic_Provider();

    ~LampIndic_Provider();

    Load_Status load();

    Unload_Status unload();

    Enable_Indications_Status enable_indications(
	Indication_Handler<LampIndic>* indication_handler);

    Disable_Indications_Status disable_indications();

    Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

private:

    static void* _thread_proc(void* arg);

    void _stop_thread();

    Indication_Handler<LampIndic>* _indication_handler;
    Mutex _indication_handler_mutex;
    Thread _thread;

    // This counter is used to signal the worker thread to exit (or return).
    Atomic_Counter _counter;
};

CIMPLE_NAMESPACE_END

#endif /* _LampIndic_Provider_h */
