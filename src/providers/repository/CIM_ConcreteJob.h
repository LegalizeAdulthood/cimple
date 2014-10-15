//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _CIM_ConcreteJob_h
#define _CIM_ConcreteJob_h

#include <cimple/cimple.h>
#include "CIM_Job.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE CIM_ConcreteJob : public Instance
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

    // CIM_ConcreteJob features:
    Property<String> InstanceID;
    Property<uint16> JobState;
    Property<Datetime> TimeOfLastStateChange;
    Property<Datetime> TimeBeforeRemoval;

    CIMPLE_CLASS(CIM_ConcreteJob)
};

typedef CIM_Job_KillJob_method CIM_ConcreteJob_KillJob_method;

class CIMPLE_LINKAGE CIM_ConcreteJob_RequestStateChange_method : public Instance
{
public:
    Property<uint16> RequestedState;
    Property<Datetime> TimeoutPeriod;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_ConcreteJob_RequestStateChange_method)
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_ConcreteJob_h */
