#ifndef _LampIndic_Provider_h
#define _LampIndic_Provider_h

#include <cimple/cimple.h>
#include "LampIndic.h"
#include <cimple/Mutex.h>
#include <cimple/Thread.h>
#include <cimple/Atomic_Counter.h>
#include <cimple/Predicate.h>

CIMPLE_NAMESPACE_BEGIN

class LampIndic_Provider
{
public:

    typedef LampIndic Class;

    LampIndic_Provider();

    CIMPLE_HIDE ~LampIndic_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Enable_Indications_Status enable_indications(
	Indication_Handler<LampIndic>* indication_handler);

    CIMPLE_HIDE Disable_Indications_Status disable_indications();

    CIMPLE_HIDE Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

    static CIMPLE_HIDE int proc(
	const Registration* registration,
	int operation, 
	void* arg0, 
	void* arg1, 
	void* arg2, 
	void* arg3,
	void* arg4,
	void* arg5,
	void* arg6,
	void* arg7);

private:

    static void* _thread_proc(void* arg);

    void _stop_thread();

    Indication_Handler<LampIndic>* _indication_handler;
    Mutex _indication_handler_mutex;
    Thread _thread;

    // This counter is used to signal the worker thread to exit (or return).
    Atomic_Counter _counter;

    // The main provider thread blocks on this object until the worker
    // thread signals it.
    Predicate _predicate;
};

CIMPLE_NAMESPACE_END

#endif /* _LampIndic_Provider_h */
