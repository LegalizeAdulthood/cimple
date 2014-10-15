/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_EnabledLogicalElement_h
#define _cimple_CIM_EnabledLogicalElement_h

#include <cimple/cimple.h>
#include "CIM_LogicalElement.h"
#include "CIM_ConcreteJob.h"

#if (0x00633500 > CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.53) is newer than the version of <cimple/cimple.h> found on the include path. Please place the matching version of <cimple/cimple.h> on the include path."
#endif

#if (0x00633500 < CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.53) is older than the version of <cimple/cimple.h> found on the include path. Please regenerate the sources with the matching version of genclass."
#endif


CIMPLE_NAMESPACE_BEGIN

class CIM_EnabledLogicalElement : public Instance
{
public:
    // CIM_ManagedElement features:
    Property<String> Caption;
    Property<String> Description;
    Property<String> ElementName;

    // CIM_ManagedSystemElement features:
    Property<Datetime> InstallDate;
    Property<String> Name;
    Property<Array_uint16> OperationalStatus;
    Property<Array_String> StatusDescriptions;
    Property<String> Status;
    Property<uint16> HealthState;

    // CIM_LogicalElement features:

    // CIM_EnabledLogicalElement features:
    Property<uint16> EnabledState;
    Property<String> OtherEnabledState;
    Property<uint16> RequestedState;
    Property<uint16> EnabledDefault;
    Property<Datetime> TimeOfLastStateChange;

    CIMPLE_CLASS(CIM_EnabledLogicalElement)
};

class CIM_EnabledLogicalElement_RequestStateChange_method : public Instance
{
public:
    Property<uint16> RequestedState;
    CIM_ConcreteJob* Job;
    Property<Datetime> TimeoutPeriod;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_EnabledLogicalElement_RequestStateChange_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_EnabledLogicalElement_h */
