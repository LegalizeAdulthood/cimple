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

    CIMPLE_HIDE ~MyIndication_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Enable_Indications_Status enable_indications(
	Indication_Handler<MyIndication>* indication_handler);

    CIMPLE_HIDE Disable_Indications_Status disable_indications();

    CIMPLE_HIDE Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

    CIMPLE_HIDE static int proc(
	int operation, void* arg0, void* arg1, void* arg2, void* arg3);

private:

    Indication_Handler<MyIndication>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _MyIndication_Provider_h */
