#include "MyIndication_Provider.h"

CIMPLE_NAMESPACE_BEGIN

MyIndication_Provider::MyIndication_Provider() : _indication_handler(0)
{
}

MyIndication_Provider::~MyIndication_Provider()
{
}

Load_Status MyIndication_Provider::load()
{
    return LOAD_OK;
}

Unload_Status MyIndication_Provider::unload()
{
    return UNLOAD_OK;
}

Timer_Status MyIndication_Provider::timer(uint64& timeout)
{
    timeout = 1000;
    printf("MyIndication_Provider::timer(%llu)\n", timeout);

#if 1
    if (_indication_handler)
    {
	MyIndication* indic = MyIndication::create();
	indic->IndicationTime.value = Datetime::now();
	_indication_handler->handle(indic);
    }
#endif

    return TIMER_RESCHEDULE;
}

Enable_Indications_Status MyIndication_Provider::enable_indications(
    Indication_Handler<MyIndication>* indication_handler)
{
    _indication_handler = indication_handler;

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status MyIndication_Provider::disable_indications()
{
    if (_indication_handler)
    {
	delete _indication_handler;
	_indication_handler = 0;
    }

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status MyIndication_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    printf("***** MyIndication_Provider::DeliverIndications()\n");

    return_value.value = 1;
    return_value.null = false;

#if 1
    if (_indication_handler)
    {
	MyIndication* indic = MyIndication::create();
	// indic->IndicationTime.value = Datetime::now();
	_indication_handler->handle(indic);
    }
#endif

    return INVOKE_METHOD_OK;
}

int MyIndication_Provider::proc(
    int operation, void* arg0, void* arg1, void* arg2, void* arg3)
{
    // CAUTION: PLEASE DO NOT MODIFY THIS FUNCTION; IT WAS AUTOMATICALLY 
    // GENERATED.

    typedef MyIndication Class;
    typedef MyIndication_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Indication_Provider_Proc_T<Provider>::proc(
	    operation, arg0, arg1, arg2, arg3);

    Provider* provider = (Provider*)arg0;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "DeliverIndications") == 0)
    {
        typedef MyIndication_DeliverIndications_method Method;
        Method* method = (Method*)arg2;
        return provider->DeliverIndications(
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
