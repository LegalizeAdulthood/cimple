/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005 Michael E. Brasher
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

using namespace cimple;

class CIMPLECMPI_LINKAGE Adapter : public Provider_Handle
{
public:

    Adapter(
        const CMPIBroker* broker_,
        const CMPIContext* context,
        const char* provider_name,
        const Registration* registration);

    ~Adapter();

    static CMPIStatus cleanup(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        CMPIBoolean terminating);

    static CMPIStatus enumInstanceNames(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op);

    static CMPIStatus enumInstances(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op,
        const char** properties);

    static CMPIStatus getInstance(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op,
        const char** properties);

    static CMPIStatus createInstance(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op,
        const CMPIInstance* cmpi_inst);

    static CMPIStatus modifyInstance(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* ref,
        const CMPIInstance* inst,
        const char** properties);

    static CMPIStatus deleteInstance(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op);

    static CMPIStatus execQuery(
        CMPIInstanceMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* ref,
        const char* lang,
        const char* query);

    static CMPIStatus methodCleanup(
        CMPIMethodMI* mi,
        const CMPIContext* context,
        CMPIBoolean terminating);

    static CMPIStatus invokeMethod(
        CMPIMethodMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* ref,
        const char* method,
        const CMPIArgs* in,
        CMPIArgs* out);

    static CMPIStatus indicationCleanup(
        CMPIIndicationMI* mi,
        const CMPIContext* context,
        CMPIBoolean terminating);

     static CMPIStatus authorizeFilter(
         CMPIIndicationMI* mi,
         const CMPIContext* ctx,
         const CMPISelectExp* se,
         const char* ns,
         const CMPIObjectPath* op,
         const char* user);

    static CMPIStatus mustPoll(
        CMPIIndicationMI* mi,
        const CMPIContext* context,
        const CMPISelectExp* filter,
        const char* indication_type,
        const CMPIObjectPath* class_path);

    static CMPIStatus activateFilter(
        CMPIIndicationMI* mi,
        const CMPIContext* context,
        const CMPISelectExp* select_expr,
        const char* indication_type,
        const CMPIObjectPath* class_path,
        CMPIBoolean first_activation);

    static CMPIStatus deactivateFilter(
        CMPIIndicationMI* mi,
        const CMPIContext* context,
        const CMPISelectExp* select_expr,
        const  char* name_space,
        const CMPIObjectPath* class_path,
        CMPIBoolean last);

    static void enableIndications(
        CMPIIndicationMI* mi,
        const CMPIContext* context);

    static void disableIndications(
        CMPIIndicationMI* mi,
        const CMPIContext* context);

    static CMPIStatus associationCleanup(
        CMPIAssociationMI* mi,
        const CMPIContext* context,
        CMPIBoolean terminating);

    static CMPIStatus associators(
        CMPIAssociationMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op,
        const char* assoc_class,
        const char* result_class,
        const char* role,
        const char* result_role,
        const char** properties);

    static CMPIStatus associatorNames(
        CMPIAssociationMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op,
        const char* assoc_class,
        const char* result_class,
        const char* role,
        const char* result_role);

    static CMPIStatus references(
        CMPIAssociationMI* mi,
        const CMPIContext* context,
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op,
        const char* result_class,
        const char* role ,
        const char** properties);

    static CMPIStatus referenceNames(
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
    const CMPIBroker* broker;

    // Number of times this provider has been loaded due to CMPI entry points
    // for different provider types (instance, method, indication, association).
    size_t load_count;

private:

    const Meta_Class* _mc;

    // This flag indicates whether indications are enabled.
    bool _indications_enabled;

    // Synchronizes access to adapter methods from different threads:
    RMutex _lock;

    // Scheduler and timer proc to drive provider timer() method.
    static Scheduler* _sched;

    static RMutex _sched_lock;
    pthread_attr_t _timer_thread_attr;
    pthread_t _timer_thread;
    size_t _timer_id;
    bool _stop_timer_thread;
    const CMPIContext* _timer_context;

    static uint64 _timer(void* arg);

    static void* _timer_thread_proc(void* arg);

    static CMPIStatus _cleanup(
        Adapter* adapter,
        const CMPIContext* context,
        CMPIBoolean terminating);

    const Meta_Class* _find_meta_class(const char* class_name);
};

#endif /* _Adapter_h */
