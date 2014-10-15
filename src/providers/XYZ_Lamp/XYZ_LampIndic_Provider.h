#ifndef _XYZ_LampIndic_Provider_h
#define _XYZ_LampIndic_Provider_h

#include <cimple/cimple.h>
#include "XYZ_LampIndic.h"

CIMPLE_NAMESPACE_BEGIN

class XYZ_LampIndic_Provider
{
public:

    typedef XYZ_LampIndic Class;

    XYZ_LampIndic_Provider();

    ~XYZ_LampIndic_Provider();

    Load_Status load();

    Unload_Status unload();

    Enable_Indications_Status enable_indications(
	Indication_Handler<XYZ_LampIndic>* indication_handler);

    Disable_Indications_Status disable_indications();

    Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

private:

    Indication_Handler<XYZ_LampIndic>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _XYZ_LampIndic_Provider_h */
