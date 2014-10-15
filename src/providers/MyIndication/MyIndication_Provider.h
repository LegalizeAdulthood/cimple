#ifndef _MyIndication_Provider_h
#define _MyIndication_Provider_h

#include <cimple/cimple.h>
#include "MyIndication.h"

CIMPLE_NAMESPACE_BEGIN

class MyIndication_Provider
{
public:

    typedef MyIndication Class;

    MyIndication_Provider();

    ~MyIndication_Provider();

    Load_Status load();

    Unload_Status unload();

    Enable_Indications_Status enable_indications(
	Indication_Handler<MyIndication>* indication_handler);

    Disable_Indications_Status disable_indications();

    Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

private:

    Indication_Handler<MyIndication>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _MyIndication_Provider_h */
