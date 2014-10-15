/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#ifndef _Adapter_h
#define _Adapter_h

#include <cimple/config.h>
#include <cmpidt.h>
#include <cmpift.h>
#include <cmpimacs.h>
#include <cimple/cimple.h>
#include <cimple/Provider_Handle.h>
#include <cimple/Scheduler.h>
#include <cimple/RMutex.h>
#include "linkage.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLECMPI_LINKAGE CMPI_Adapter : public Provider_Handle
{
public:

    CMPI_Adapter(
	const CMPIBroker* broker_, 
	const CMPIContext* context,
	const char* provider_name,
	const Registration* registration,
	CMPI_Adapter*& adapter_back_pointer);

    ~CMPI_Adapter();

    CIMPLE_HIDE static CMPIStatus cleanup(
	CMPIInstanceMI* mi, 
	const CMPIContext* context,
	CMPIBoolean terminating);

    CIMPLE_HIDE static CMPIStatus enumInstanceNames(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op);

    CIMPLE_HIDE static CMPIStatus enumInstances(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op, 
	const char** properties);

    CIMPLE_HIDE static CMPIStatus getInstance(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op, 
	const char** properties);

    CIMPLE_HIDE static CMPIStatus createInstance(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op, 
	const CMPIInstance* cmpi_inst);

    CIMPLE_HIDE static CMPIStatus modifyInstance(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* ref, 
	const CMPIInstance* inst,
	const char** properties);

    CIMPLE_HIDE static CMPIStatus deleteInstance(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op);

    CIMPLE_HIDE static CMPIStatus execQuery(
	CMPIInstanceMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* ref, 
	const char* lang, 
	const char* query);

    CIMPLE_HIDE static CMPIStatus methodCleanup(
	CMPIMethodMI* mi, 
	const CMPIContext* context,
	CMPIBoolean terminating);

    CIMPLE_HIDE static CMPIStatus invokeMethod(
	CMPIMethodMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* ref, 
	const char* method, 
	const CMPIArgs* in,
	CMPIArgs* out);

    CIMPLE_HIDE static CMPIStatus indicationCleanup(
	CMPIIndicationMI* mi, 
	const CMPIContext* context,
	CMPIBoolean terminating);

     CIMPLE_HIDE static CMPIStatus authorizeFilter(
	 CMPIIndicationMI* mi, 
	 const CMPIContext* ctx,
	 const CMPISelectExp* se, 
	 const char* ns, 
	 const CMPIObjectPath* op,
	 const char* user);

    CIMPLE_HIDE static CMPIStatus mustPoll(
	CMPIIndicationMI* mi, 
	const CMPIContext* context,
	const CMPISelectExp* filter, 
	const char* indication_type,
	const CMPIObjectPath* class_path);

    CIMPLE_HIDE static CMPIStatus activateFilter(
	CMPIIndicationMI* mi, 
	const CMPIContext* context,
	const CMPISelectExp* select_expr, 
	const char* indication_type,
	const CMPIObjectPath* class_path, 
	CMPIBoolean first_activation);

    CIMPLE_HIDE static CMPIStatus deactivateFilter(
	CMPIIndicationMI* mi, 
	const CMPIContext* context,
	const CMPISelectExp* select_expr, 
	const  char* name_space,
	const CMPIObjectPath* class_path, 
	CMPIBoolean last);

    CIMPLE_HIDE static void enableIndications(
	CMPIIndicationMI* mi, 
	const CMPIContext* context);

    CIMPLE_HIDE static void disableIndications(
	CMPIIndicationMI* mi, 
	const CMPIContext* context);

    CIMPLE_HIDE static CMPIStatus associationCleanup(
	CMPIAssociationMI* mi, 
	const CMPIContext* context,
	CMPIBoolean terminating);

    CIMPLE_HIDE static CMPIStatus associators( 
	CMPIAssociationMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op, 
	const char* assoc_class, 
	const char* result_class,
	const char* role, 
	const char* result_role, 
	const char** properties);

    CIMPLE_HIDE static CMPIStatus associatorNames(
	CMPIAssociationMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op, 
	const char* assoc_class, 
	const char* result_class,
	const char* role, 
	const char* result_role);

    CIMPLE_HIDE static CMPIStatus references(
	CMPIAssociationMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
	const char* result_class, 
	const char* role ,
	const char** properties);

    CIMPLE_HIDE static CMPIStatus referenceNames(
	CMPIAssociationMI* mi, 
	const CMPIContext* context, 
	const CMPIResult* result,
	const CMPIObjectPath* cmpi_op, 
	const char* result_class, 
	const char* role);

    CMPIInstanceMIFT instance_ft;
    CMPIMethodMIFT method_ft;
    CMPIIndicationMIFT indication_ft;
    CMPIAssociationMIFT association_ft;

    CMPIInstanceMI instance_mi;
    CMPIMethodMI method_mi;
    CMPIAssociationMI association_mi;
    CMPIIndicationMI indication_mi;

    const CMPIBroker* broker;

    // Number of times this provider has been loaded due to CMPI entry points
    // for different provider types (instance, method, indication, association).
    size_t load_count;

    // ATTN: make prviate?
    const CMPIContext* current_context;

private:

    const Meta_Class* _mc;

    // This flag indicates whether indications are enabled.
    bool _indications_enabled;

    // This points back to the static place in the entry point that points
    // to this adapter.
    CMPI_Adapter*& _adapter_back_pointer;

    // Synchronizes access to adapter methods from different threads:
    RMutex _lock;

    // Scheduler and timer proc to drive provider timer() method.
    CIMPLE_HIDE static Scheduler* _sched;

    CIMPLE_HIDE static RMutex _sched_lock;
    pthread_attr_t _timer_thread_attr;
    pthread_t _timer_thread;
    size_t _timer_id;
    bool _stop_timer_thread;
    const CMPIContext* _timer_context;

    CIMPLE_HIDE static uint64 _timer(void* arg);

    CIMPLE_HIDE static void* _timer_thread_proc(void* arg);

    CIMPLE_HIDE static CMPIStatus _cleanup(
	CMPI_Adapter* adapter,
	const CMPIContext* context,
	CMPIBoolean terminating);

    CIMPLE_HIDE const Meta_Class* _find_meta_class(const char* class_name);
};

CIMPLE_NAMESPACE_END

#endif /* _Adapter_h */
