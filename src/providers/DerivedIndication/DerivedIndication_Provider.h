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

    CIMPLE_HIDE ~DerivedIndication_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Enable_Indications_Status enable_indications(
	Indication_Handler<DerivedIndication>* indication_handler);

    CIMPLE_HIDE Disable_Indications_Status disable_indications();

    CIMPLE_HIDE Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

    static int proc(
	const Registration* registration,
	int operation, 
	void* arg0, 
	void* arg1, 
	void* arg2, 
	void* arg3,
	void* arg4,
	void* arg5,
	void* arg6,
	void* arg7);

private:

    Indication_Handler<DerivedIndication>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _DerivedIndication_Provider_h */
