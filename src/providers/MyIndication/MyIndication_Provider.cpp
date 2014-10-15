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

Enable_Indications_Status MyIndication_Provider::enable_indications(
    Indication_Handler<MyIndication>* indication_handler)
{
    // printf("=== MyIndication_Provider::enable_indications()\n");
	// This is part of genprov generatedskeleton
    _indication_handler = indication_handler;

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status MyIndication_Provider::disable_indications()
{
    // printf("=== MyIndication_Provider::disable_indications()\n");

    // Delete indication handler. The Provider MUST delete this handler
    // This is installed as part of genprov  generated skeleton
    if(_indication_handler)
        delete _indication_handler;

    // Destroy pointer to indication handler. This serves as a flag
    // for the indication generation method
    // Part of standard genprov generated skeleton
    _indication_handler = 0;

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status MyIndication_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    // printf("=== MyIndication_Provider::DeliverIndications()\n");

    return_value.value = 99;
    return_value.null = false;

    // The existence of _indication_handler is used to determine of
    // indications are enabled.
    
    if (_indication_handler)
    {
        MyIndication* indic = MyIndication_create("777", "seven");
        _indication_handler->handle(indic);
    }

    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END

