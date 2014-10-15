#include "XYZ_LampIndic_Provider.h"

CIMPLE_NAMESPACE_BEGIN

XYZ_LampIndic_Provider::XYZ_LampIndic_Provider() : _indication_handler(0)
{
}

XYZ_LampIndic_Provider::~XYZ_LampIndic_Provider()
{
}

Load_Status XYZ_LampIndic_Provider::load()
{
    return LOAD_OK;
}

Unload_Status XYZ_LampIndic_Provider::unload()
{
    return UNLOAD_OK;
}

Enable_Indications_Status XYZ_LampIndic_Provider::enable_indications(
    Indication_Handler<XYZ_LampIndic>* indication_handler)
{
    _indication_handler = indication_handler;

    return ENABLE_INDICATIONS_OK;
}

Disable_Indications_Status XYZ_LampIndic_Provider::disable_indications()
{
    if (_indication_handler)
    {
        delete _indication_handler;
        _indication_handler = 0;
    }

    return DISABLE_INDICATIONS_OK;
}

Invoke_Method_Status XYZ_LampIndic_Provider::DeliverIndications(
    Property<uint32>& return_value)
{
    return INVOKE_METHOD_UNSUPPORTED;
}

CIMPLE_NAMESPACE_END

