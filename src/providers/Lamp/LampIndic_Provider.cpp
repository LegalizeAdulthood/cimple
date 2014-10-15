#include <cimple/Time.h>
#include <pthread.h>
#include <unistd.h>
#include "LampIndic_Provider.h"

#if 0
# define TRACE CIMPLE_TRACE
#else
# define TRACE
#endif

CIMPLE_NAMESPACE_BEGIN

static void _send_indication(
    const char* func, 
    Indication_Handler<LampIndic>* handler)
{
    TRACE;

    // printf("func: %s\n", func);

    if (handler)
    {
	LampIndic* indic = LampIndic::create();
	indic->IndicationIdentifier.value = "GOODBYE";
	indic->IndicationIdentifier.null = false;
	handler->handle(indic);
    }
}

void* LampIndic_Provider::_thread_proc(void* arg)
{
    LampIndic_Provider* provider = (LampIndic_Provider*)arg;

    TRACE;

    for (size_t i = 0; i < 500; i++)
    {
	// We must synchronize access to the handler since the provider's
	// main thread also accesses it.

	provider->_indication_handler_mutex.lock();
	_send_indication("_thread_proc()", provider->_indication_handler);
	provider->_indication_handler_mutex.unlock();

	// Stay in this loop for one second.

	for (size_t i = 0; i < 100; i++)
	{
	    // See if main thread has asked us to quit by decrementing the
	    // counter to zero.

	    if (provider->_counter.get() == 0)
	    {
		// The main thread is waiting on this signal. Signal it so
		// it can continue.
		Thread::exit(0);
		return 0;
	    }

	    // Sleep no longer than 10 miliseconds.
	    Time::sleep(10 * Time::MSEC);
	}
    }

    return 0;
}

LampIndic_Provider::LampIndic_Provider() : _indication_handler(0), _counter(0)
{
    TRACE;
}

LampIndic_Provider::~LampIndic_Provider()
{
    TRACE;
}

Load_Status LampIndic_Provider::load()
{
    TRACE;

    return LOAD_OK;
}

Unload_Status LampIndic_Provider::unload()
{
    TRACE;
    _stop_thread();
    return UNLOAD_OK;
}

Timer_Status LampIndic_Provider::timer(uint64& timeout)
{
    TRACE;

    timeout = 1000;

    _indication_handler_mutex.lock();
    _send_indication("timer()", _indication_handler);
    _indication_handler_mutex.unlock();

    return TIMER_RESCHEDULE;
}

Enable_Indications_Status LampIndic_Provider::enable_indications(
    Indication_Handler<LampIndic>* indication_handler)
{
    TRACE;

    // Since three threads share the same indication  handler, we use a mutex.

    _indication_handler_mutex.lock();
    _indication_handler = indication_handler;
    _indication_handler_mutex.unlock();

    // Create a thread to send indications. Increment counter to one first
    // to indicate that the worker thread has been created.

    _counter.inc();
    Thread::create_joinable(_thread, (Thread_Proc)_thread_proc, this);

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status LampIndic_Provider::disable_indications()
{
    TRACE;

    _stop_thread();

    _indication_handler_mutex.lock();

    if (_indication_handler)
	delete _indication_handler;

    _indication_handler_mutex.unlock();

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status LampIndic_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    TRACE;

    _indication_handler_mutex.lock();
    _send_indication("DeliverIndications()", _indication_handler);
    _indication_handler_mutex.unlock();

    // Never return null.
    return_value.null = false;

    return INVOKE_METHOD_OK;
}

int LampIndic_Provider::proc(
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
    TRACE;
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef LampIndic Class;
    typedef LampIndic_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Indication_Provider_Proc_T<Provider>::proc(registration,
	    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "DeliverIndications") == 0)
    {
        typedef LampIndic_DeliverIndications_method Method;
        Method* method = (Method*)arg2;
        return provider->DeliverIndications(
            method->return_value);
    }
    return -1;
}

void LampIndic_Provider::_stop_thread()
{
    TRACE;

    if (_counter.get() == 1)
    {
	// Signal the other thread by decrementing the counter to zero.
	_counter.dec();

	void* value_ptr;
	Thread::join(_thread, value_ptr);
    }
}

CIMPLE_NAMESPACE_END
