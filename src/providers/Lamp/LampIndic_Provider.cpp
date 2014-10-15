#include "LampIndic_Provider.h"

CIMPLE_NAMESPACE_BEGIN

LampIndic_Provider::LampIndic_Provider() : _indication_handler(0)
{
}

LampIndic_Provider::~LampIndic_Provider()
{
}

Load_Status LampIndic_Provider::load()
{
    return LOAD_OK;
}

Unload_Status LampIndic_Provider::unload()
{
    return UNLOAD_OK;
}

Timer_Status LampIndic_Provider::timer(uint64& timeout)
{
    return TIMER_CANCEL;
}

Enable_Indications_Status LampIndic_Provider::enable_indications(
    Indication_Handler<LampIndic>* indication_handler)
{
    _indication_handler = indication_handler;

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status LampIndic_Provider::disable_indications()
{
    if (_indication_handler)
    {
	delete _indication_handler;
	_indication_handler = 0;
    }

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status LampIndic_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    LampIndic* indic = LampIndic::create();

    indic->IndicationIdentifier.value = "HELLO";
    indic->IndicationIdentifier.null = false;

    _indication_handler->handle(indic);

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

CIMPLE_NAMESPACE_END
