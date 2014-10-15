#ifndef _DerivedIndication_Provider_h
#define _DerivedIndication_Provider_h

#include <cimple/cimple.h>
#include "DerivedIndication.h"

CIMPLE_NAMESPACE_BEGIN

class DerivedIndication_Provider
{
public:

    typedef DerivedIndication Class;

    DerivedIndication_Provider();

    ~DerivedIndication_Provider();

    Load_Status load();

    Unload_Status unload();

    Enable_Indications_Status enable_indications(
	Indication_Handler<DerivedIndication>* indication_handler);

    Disable_Indications_Status disable_indications();

    Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

private:

    Indication_Handler<DerivedIndication>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _DerivedIndication_Provider_h */
