#include "DerivedIndication_Provider.h"

CIMPLE_NAMESPACE_BEGIN

DerivedIndication_Provider::DerivedIndication_Provider() : 
    _indication_handler(0)
{
}

DerivedIndication_Provider::~DerivedIndication_Provider()
{
}

Load_Status DerivedIndication_Provider::load()
{
    return LOAD_OK;
}

Unload_Status DerivedIndication_Provider::unload()
{
    return UNLOAD_OK;
}

Enable_Indications_Status DerivedIndication_Provider::enable_indications(
    Indication_Handler<DerivedIndication>* indication_handler)
{
    printf("=== DerivedIndication_Provider::enable_indications()\n");

    _indication_handler = indication_handler;

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status DerivedIndication_Provider::disable_indications()
{
    printf("=== DerivedIndication_Provider::disable_indications()\n");

    if (_indication_handler)
    {
        delete _indication_handler;
        _indication_handler = 0;
    }

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status DerivedIndication_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    printf("=== DerivedIndication_Provider::DeliverIndications()\n");

    return_value.value = 99;
    return_value.null = false;

    if (_indication_handler)
    {
        DerivedIndication* indic = DerivedIndication::create();

        indic->IndicationIdentifier.value = "888";
        indic->IndicationIdentifier.null = false;

        indic->IndicationTime.value = Datetime::now();
        indic->IndicationTime.null = false;

        _indication_handler->handle(indic);
    }

    return INVOKE_METHOD_OK;
}

CIMPLE_NAMESPACE_END

