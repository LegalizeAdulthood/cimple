#include <cimple/Time.h>
#include <pthread.h>
#include <unistd.h>
#include "LampIndic_Provider.h"
#include "LampIndicA.h"
#include "LampIndicB.h"
#include "LampIndicC.h"

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

    char utf8_chars[] = 
    {
        '\xCE', '\x99', '\xCE', '\xBF', '\xCF', '\x8D',
        '\xCE', '\xBD', '\xCE', '\xB9', '\xCE', '\xBA',
        '\xCE', '\xBF', '\xCE', '\xBD', '\xCF', '\x84',
        '\0'
    };

    // printf("func: %s\n", func);

    if (handler)
    {
        LampIndicA* indic = LampIndicA::create();
        indic->IndicationIdentifier.set("GOODBYE");
#if 0
        indic->message.set("Same old message");
#else
        indic->message.set(utf8_chars);
#endif

        LampIndic* tmp = cast<LampIndic*>(indic);

        handler->handle(tmp);
    }
}

void* LampIndic_Provider::_thread_proc(void* arg)
{
    LampIndic_Provider* provider = (LampIndic_Provider*)arg;

    TRACE;

    // ATTN: This sleep prevents a "Recursive Use of CIMOMHandle Attempted" 
    // message from Pegasus ClientCIMOMHandleAccessController() in
    // ClientCIMOMHandleRep.cpp.
    sleep(1);

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

