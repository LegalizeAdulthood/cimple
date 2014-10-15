#include "MyIndication_Provider.h"
#include "MyEmbeddedClass.h"

CIMPLE_NAMESPACE_BEGIN

MyIndication* MyIndication_create(
    const char* IndicationIdentifier,
    const char* msg)
{
    MyIndication* indic = MyIndication::create();

    indic->IndicationIdentifier.value = IndicationIdentifier;
    indic->IndicationTime.value = Datetime::now();

    MyEmbeddedClass* embed = MyEmbeddedClass::create();
    embed->msg.value = msg;

    indic->object = embed;

    return indic;
}

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

Timer_Status MyIndication_Provider::timer(uint64& timeout_msec)
{
    if (_indication_handler)
    {
	MyIndication* indic = MyIndication_create("9999", "nine");
	// print(indic);
	_indication_handler->handle(indic);
    }

    timeout_msec = 1000;
    return TIMER_RESCHEDULE;
}

Enable_Indications_Status MyIndication_Provider::enable_indications(
    Indication_Handler<MyIndication>* indication_handler)
{
    printf("=== MyIndication_Provider::enable_indications()\n");

    _indication_handler = indication_handler;

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status MyIndication_Provider::disable_indications()
{
    printf("=== MyIndication_Provider::disable_indications()\n");

    delete _indication_handler;
    _indication_handler = 0;

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status MyIndication_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    printf("=== MyIndication_Provider::DeliverIndications()\n");

    return_value.value = 99;
    return_value.null = false;

    if (_indication_handler)
    {
	MyIndication* indic = MyIndication_create("777", "seven");
	// print(indic);
	_indication_handler->handle(indic);
    }

    return INVOKE_METHOD_OK;
}

int MyIndication_Provider::proc(
    int operation, void* arg0, void* arg1, void* arg2, void* arg3)
{
    typedef MyIndication Class;
    typedef MyIndication_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Indication_Provider_Proc_T<Provider>::proc(
	    operation, arg0, arg1, arg2, arg3);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
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
