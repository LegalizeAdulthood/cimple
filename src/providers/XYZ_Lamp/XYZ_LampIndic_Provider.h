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

    CIMPLE_HIDE ~XYZ_LampIndic_Provider();

    CIMPLE_HIDE Load_Status load();

    CIMPLE_HIDE Unload_Status unload();

    CIMPLE_HIDE Timer_Status timer(uint64& timeout_msec);

    CIMPLE_HIDE Enable_Indications_Status enable_indications(
	Indication_Handler<XYZ_LampIndic>* indication_handler);

    CIMPLE_HIDE Disable_Indications_Status disable_indications();

    CIMPLE_HIDE Invoke_Method_Status DeliverIndications(
        Property<uint32>& return_value);

    static CIMPLE_HIDE int proc(
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

    Indication_Handler<XYZ_LampIndic>* _indication_handler;
};

CIMPLE_NAMESPACE_END

#endif /* _XYZ_LampIndic_Provider_h */
