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

int XYZ_LampIndic_Provider::proc(
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

    typedef XYZ_LampIndic Class;
    typedef XYZ_LampIndic_Provider Provider;

    if (operation != OPERATION_INVOKE_METHOD)
        return Indication_Provider_Proc_T<Provider>::proc(registration,
	    operation, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    Provider* provider = (Provider*)arg0;
    const Class* self = (const Class*)arg1;
    const char* meth_name = ((Instance*)arg2)->meta_class->name;

    if (strcasecmp(meth_name, "DeliverIndications") == 0)
    {
        typedef XYZ_LampIndic_DeliverIndications_method Method;
        Method* method = (Method*)arg2;
        return provider->DeliverIndications(
            method->return_value);
    }
    return -1;
}

CIMPLE_NAMESPACE_END
