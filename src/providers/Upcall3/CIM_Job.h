/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_Job_h
#define _cimple_CIM_Job_h

#include <cimple/cimple.h>
#include "CIM_LogicalElement.h"

#if (0x00632900 > CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.41) is newer than the version of <cimple/cimple.h> found on the include path. Please place the matching version of <cimple/cimple.h> on the include path."
#endif

#if (0x00632900 < CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.41) is older than the version of <cimple/cimple.h> found on the include path. Please regenerate the sources with the matching version of genclass."
#endif


CIMPLE_NAMESPACE_BEGIN

class CIM_Job : public Instance
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

    // CIM_Job features:
    Property<String> JobStatus;
    Property<Datetime> TimeSubmitted;
    Property<Datetime> ScheduledStartTime;
    Property<Datetime> StartTime;
    Property<Datetime> ElapsedTime;
    Property<uint32> JobRunTimes;
    Property<uint8> RunMonth;
    Property<sint8> RunDay;
    Property<sint8> RunDayOfWeek;
    Property<Datetime> RunStartInterval;
    Property<uint16> LocalOrUtcTime;
    Property<Datetime> UntilTime;
    Property<String> Notify;
    Property<String> Owner;
    Property<uint32> Priority;
    Property<uint16> PercentComplete;
    Property<boolean> DeleteOnCompletion;
    Property<uint16> ErrorCode;
    Property<String> ErrorDescription;
    Property<uint16> RecoveryAction;
    Property<String> OtherRecoveryAction;

    CIMPLE_CLASS(CIM_Job)
};

class CIM_Job_KillJob_method : public Instance
{
public:
    Property<boolean> DeleteOnKill;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_Job_KillJob_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_Job_h */
