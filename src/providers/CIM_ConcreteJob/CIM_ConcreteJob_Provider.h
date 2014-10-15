#ifndef _CIM_ConcreteJob_Provider_h
#define _CIM_ConcreteJob_Provider_h

#include <cimple/cimple.h>
#include "CIM_ConcreteJob.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_ConcreteJob_Provider
{
public:

    typedef CIM_ConcreteJob Class;

    CIM_ConcreteJob_Provider();

    ~CIM_ConcreteJob_Provider();

    Load_Status load();

    Unload_Status unload();

    Get_Instance_Status get_instance(
        const CIM_ConcreteJob* model,
        CIM_ConcreteJob*& instance);

    Enum_Instances_Status enum_instances(
        const CIM_ConcreteJob* model,
        Enum_Instances_Handler<CIM_ConcreteJob>* handler);

    Create_Instance_Status create_instance(
        CIM_ConcreteJob* instance);

    Delete_Instance_Status delete_instance(
        const CIM_ConcreteJob* instance);

    Modify_Instance_Status modify_instance(
        const CIM_ConcreteJob* model,
        const CIM_ConcreteJob* instance);

    Invoke_Method_Status KillJob(
        const CIM_ConcreteJob* self,
        const Property<boolean>& DeleteOnKill,
        Property<uint32>& return_value);

    Invoke_Method_Status RequestStateChange(
        const CIM_ConcreteJob* self,
        const Property<uint16>& RequestedState,
        const Property<Datetime>& TimeoutPeriod,
        Property<uint32>& return_value);
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_ConcreteJob_Provider_h */
