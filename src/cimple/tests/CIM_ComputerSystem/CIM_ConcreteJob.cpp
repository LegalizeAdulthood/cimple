/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_ConcreteJob.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_69D23245692F148583C3BB5CD09F2371;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property
_CIM_ConcreteJob_Name;

const Meta_Property
_CIM_ConcreteJob_Name =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "Name",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,Name),
    0, /* value */
};

extern const Meta_Property
_CIM_ManagedSystemElement_OperationalStatus;

extern const Meta_Property
_CIM_ManagedSystemElement_StatusDescriptions;

extern const Meta_Property
_CIM_ManagedSystemElement_Status;

extern const Meta_Property
_CIM_ManagedSystemElement_HealthState;

extern const Meta_Property
_CIM_Job_JobStatus;

extern const Meta_Property
_CIM_Job_TimeSubmitted;

extern const Meta_Property
_CIM_Job_ScheduledStartTime;

extern const Meta_Property
_CIM_Job_StartTime;

extern const Meta_Property
_CIM_Job_ElapsedTime;

extern const Meta_Property
_CIM_Job_JobRunTimes;

extern const Meta_Property
_CIM_Job_RunMonth;

extern const Meta_Property
_CIM_Job_RunDay;

extern const Meta_Property
_CIM_Job_RunDayOfWeek;

extern const Meta_Property
_CIM_Job_RunStartInterval;

extern const Meta_Property
_CIM_Job_LocalOrUtcTime;

extern const Meta_Property
_CIM_Job_UntilTime;

extern const Meta_Property
_CIM_Job_Notify;

extern const Meta_Property
_CIM_Job_Owner;

extern const Meta_Property
_CIM_Job_Priority;

extern const Meta_Property
_CIM_Job_PercentComplete;

extern const Meta_Property
_CIM_Job_DeleteOnCompletion;

extern const Meta_Property
_CIM_Job_ErrorCode;

extern const Meta_Property
_CIM_Job_ErrorDescription;

extern const Meta_Property
_CIM_Job_RecoveryAction;

extern const Meta_Property
_CIM_Job_OtherRecoveryAction;

extern const Meta_Property
_CIM_ConcreteJob_InstanceID;

const Meta_Property
_CIM_ConcreteJob_InstanceID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "InstanceID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,InstanceID),
    0, /* value */
};

extern const Meta_Property
_CIM_ConcreteJob_JobState;

const Meta_Property
_CIM_ConcreteJob_JobState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "JobState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,JobState),
    0, /* value */
};

extern const Meta_Property
_CIM_ConcreteJob_TimeOfLastStateChange;

const Meta_Property
_CIM_ConcreteJob_TimeOfLastStateChange =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TimeOfLastStateChange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,TimeOfLastStateChange),
    0, /* value */
};

static const Meta_Property
_CIM_ConcreteJob_RequestStateChange_RequestedState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "RequestedState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0,
    CIMPLE_OFF(CIM_ConcreteJob_RequestStateChange_method,RequestedState),
    0, /* value */
};

static const Meta_Property
_CIM_ConcreteJob_RequestStateChange_TimeoutPeriod =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "TimeoutPeriod",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CIM_ConcreteJob_RequestStateChange_method,TimeoutPeriod),
    0, /* value */
};

static const Meta_Property
_CIM_ConcreteJob_RequestStateChange_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_ConcreteJob_RequestStateChange_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_ConcreteJob_RequestStateChange_MFA[] =
{
    (Meta_Feature*)&_CIM_ConcreteJob_RequestStateChange_RequestedState,
    (Meta_Feature*)&_CIM_ConcreteJob_RequestStateChange_TimeoutPeriod,
    (Meta_Feature*)&_CIM_ConcreteJob_RequestStateChange_return_value
};

const Meta_Method
CIM_ConcreteJob_RequestStateChange_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "RequestStateChange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_ConcreteJob_RequestStateChange_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_ConcreteJob_RequestStateChange_MFA),
    sizeof(CIM_ConcreteJob_RequestStateChange_method),
    UINT32,
};

extern const Meta_Property
_CIM_ConcreteJob_TimeBeforeRemoval;

static const Meta_Value_Scalar<const char*>
_CIM_ConcreteJob_TimeBeforeRemoval_MV =
{
    "00000000000500.000000:000"
};

const Meta_Property
_CIM_ConcreteJob_TimeBeforeRemoval =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED|CIMPLE_FLAG_WRITE,
    "TimeBeforeRemoval",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,TimeBeforeRemoval),
    (const Meta_Value*)&_CIM_ConcreteJob_TimeBeforeRemoval_MV,
};

static Meta_Feature* _CIM_ConcreteJob_MFA[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)&_CIM_ConcreteJob_Name,
    (Meta_Feature*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)&_CIM_ManagedSystemElement_HealthState,
    (Meta_Feature*)&_CIM_Job_JobStatus,
    (Meta_Feature*)&_CIM_Job_TimeSubmitted,
    (Meta_Feature*)&_CIM_Job_ScheduledStartTime,
    (Meta_Feature*)&_CIM_Job_StartTime,
    (Meta_Feature*)&_CIM_Job_ElapsedTime,
    (Meta_Feature*)&_CIM_Job_JobRunTimes,
    (Meta_Feature*)&_CIM_Job_RunMonth,
    (Meta_Feature*)&_CIM_Job_RunDay,
    (Meta_Feature*)&_CIM_Job_RunDayOfWeek,
    (Meta_Feature*)&_CIM_Job_RunStartInterval,
    (Meta_Feature*)&_CIM_Job_LocalOrUtcTime,
    (Meta_Feature*)&_CIM_Job_UntilTime,
    (Meta_Feature*)&_CIM_Job_Notify,
    (Meta_Feature*)&_CIM_Job_Owner,
    (Meta_Feature*)&_CIM_Job_Priority,
    (Meta_Feature*)&_CIM_Job_PercentComplete,
    (Meta_Feature*)&_CIM_Job_DeleteOnCompletion,
    (Meta_Feature*)&_CIM_Job_ErrorCode,
    (Meta_Feature*)&_CIM_Job_ErrorDescription,
    (Meta_Feature*)&_CIM_Job_RecoveryAction,
    (Meta_Feature*)&_CIM_Job_OtherRecoveryAction,
    (Meta_Feature*)&CIM_Job_KillJob_method::static_meta_class,
    (Meta_Feature*)&_CIM_ConcreteJob_InstanceID,
    (Meta_Feature*)&_CIM_ConcreteJob_JobState,
    (Meta_Feature*)&_CIM_ConcreteJob_TimeOfLastStateChange,
    (Meta_Feature*)&CIM_ConcreteJob_RequestStateChange_method::static_meta_class,
    (Meta_Feature*)&_CIM_ConcreteJob_TimeBeforeRemoval,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {0},
    {1},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_ConcreteJob::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_ConcreteJob",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_ConcreteJob_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_ConcreteJob_MFA),
    sizeof(CIM_ConcreteJob),
    _locals,
    &CIM_Job::static_meta_class,
    1, /* num_keys */
    0xE68CD3C9, /* crc */
    &__meta_repository_69D23245692F148583C3BB5CD09F2371,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/CIM_ComputerSystem/CIM_ConcreteJob.cpp,v 1.7 2007/03/23 17:06:09 mbrasher-public Exp $");
