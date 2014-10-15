/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_ConcreteJob.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedElement_Caption;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedElement_Description;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedElement_ElementName;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

/*[1302]*/
extern const Meta_Property
_CIM_ConcreteJob_Name;

/*[1325]*/
const Meta_Property
_CIM_ConcreteJob_Name =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "Name",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,Name),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_OperationalStatus;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_StatusDescriptions;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_Status;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_HealthState;

/*[1302]*/
extern const Meta_Property
_CIM_Job_JobStatus;

/*[1302]*/
extern const Meta_Property
_CIM_Job_TimeSubmitted;

/*[1302]*/
extern const Meta_Property
_CIM_Job_ScheduledStartTime;

/*[1302]*/
extern const Meta_Property
_CIM_Job_StartTime;

/*[1302]*/
extern const Meta_Property
_CIM_Job_ElapsedTime;

/*[1302]*/
extern const Meta_Property
_CIM_Job_JobRunTimes;

/*[1302]*/
extern const Meta_Property
_CIM_Job_RunMonth;

/*[1302]*/
extern const Meta_Property
_CIM_Job_RunDay;

/*[1302]*/
extern const Meta_Property
_CIM_Job_RunDayOfWeek;

/*[1302]*/
extern const Meta_Property
_CIM_Job_RunStartInterval;

/*[1302]*/
extern const Meta_Property
_CIM_Job_LocalOrUtcTime;

/*[1302]*/
extern const Meta_Property
_CIM_Job_UntilTime;

/*[1302]*/
extern const Meta_Property
_CIM_Job_Notify;

/*[1302]*/
extern const Meta_Property
_CIM_Job_Owner;

/*[1302]*/
extern const Meta_Property
_CIM_Job_Priority;

/*[1302]*/
extern const Meta_Property
_CIM_Job_PercentComplete;

/*[1302]*/
extern const Meta_Property
_CIM_Job_DeleteOnCompletion;

/*[1302]*/
extern const Meta_Property
_CIM_Job_ErrorCode;

/*[1302]*/
extern const Meta_Property
_CIM_Job_ErrorDescription;

/*[1302]*/
extern const Meta_Property
_CIM_Job_RecoveryAction;

/*[1302]*/
extern const Meta_Property
_CIM_Job_OtherRecoveryAction;

/*[1302]*/
extern const Meta_Property
_CIM_ConcreteJob_InstanceID;

/*[1325]*/
const Meta_Property
_CIM_ConcreteJob_InstanceID =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "InstanceID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,InstanceID),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_CIM_ConcreteJob_JobState;

/*[1325]*/
const Meta_Property
_CIM_ConcreteJob_JobState =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "JobState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,JobState),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_CIM_ConcreteJob_TimeOfLastStateChange;

/*[1325]*/
const Meta_Property
_CIM_ConcreteJob_TimeOfLastStateChange =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TimeOfLastStateChange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,TimeOfLastStateChange),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_CIM_ConcreteJob_RequestStateChange_RequestedState =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "RequestedState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0,
    CIMPLE_OFF(CIM_ConcreteJob_RequestStateChange_method,RequestedState),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_CIM_ConcreteJob_RequestStateChange_TimeoutPeriod =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "TimeoutPeriod",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CIM_ConcreteJob_RequestStateChange_method,TimeoutPeriod),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_CIM_ConcreteJob_RequestStateChange_return_value =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_ConcreteJob_RequestStateChange_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _CIM_ConcreteJob_RequestStateChange_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_RequestStateChange_RequestedState,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_RequestStateChange_TimeoutPeriod,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_RequestStateChange_return_value
};

/*[1847]*/
const Meta_Method
CIM_ConcreteJob_RequestStateChange_method::static_meta_class =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_METHOD,
    "RequestStateChange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_ConcreteJob_RequestStateChange_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_ConcreteJob_RequestStateChange_MFA),
    sizeof(CIM_ConcreteJob_RequestStateChange_method),
    UINT32,
};

/*[1302]*/
extern const Meta_Property
_CIM_ConcreteJob_TimeBeforeRemoval;

/*[274]*/
static const Meta_Value_Scalar<const char*>
_CIM_ConcreteJob_TimeBeforeRemoval_MV =
{
    "00000000000500.000000:000"
};

/*[1325]*/
const Meta_Property
_CIM_ConcreteJob_TimeBeforeRemoval =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED|CIMPLE_FLAG_WRITE,
    "TimeBeforeRemoval",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_ConcreteJob,TimeBeforeRemoval),
    (const Meta_Value*)(void*)&_CIM_ConcreteJob_TimeBeforeRemoval_MV,
};

/*[2025]*/
static Meta_Feature* _CIM_ConcreteJob_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_Name,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_HealthState,
    (Meta_Feature*)(void*)&_CIM_Job_JobStatus,
    (Meta_Feature*)(void*)&_CIM_Job_TimeSubmitted,
    (Meta_Feature*)(void*)&_CIM_Job_ScheduledStartTime,
    (Meta_Feature*)(void*)&_CIM_Job_StartTime,
    (Meta_Feature*)(void*)&_CIM_Job_ElapsedTime,
    (Meta_Feature*)(void*)&_CIM_Job_JobRunTimes,
    (Meta_Feature*)(void*)&_CIM_Job_RunMonth,
    (Meta_Feature*)(void*)&_CIM_Job_RunDay,
    (Meta_Feature*)(void*)&_CIM_Job_RunDayOfWeek,
    (Meta_Feature*)(void*)&_CIM_Job_RunStartInterval,
    (Meta_Feature*)(void*)&_CIM_Job_LocalOrUtcTime,
    (Meta_Feature*)(void*)&_CIM_Job_UntilTime,
    (Meta_Feature*)(void*)&_CIM_Job_Notify,
    (Meta_Feature*)(void*)&_CIM_Job_Owner,
    (Meta_Feature*)(void*)&_CIM_Job_Priority,
    (Meta_Feature*)(void*)&_CIM_Job_PercentComplete,
    (Meta_Feature*)(void*)&_CIM_Job_DeleteOnCompletion,
    (Meta_Feature*)(void*)&_CIM_Job_ErrorCode,
    (Meta_Feature*)(void*)&_CIM_Job_ErrorDescription,
    (Meta_Feature*)(void*)&_CIM_Job_RecoveryAction,
    (Meta_Feature*)(void*)&_CIM_Job_OtherRecoveryAction,
    (Meta_Feature*)(void*)&CIM_Job_KillJob_method::static_meta_class,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_InstanceID,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_JobState,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_TimeOfLastStateChange,
    (Meta_Feature*)(void*)&CIM_ConcreteJob_RequestStateChange_method::static_meta_class,
    (Meta_Feature*)(void*)&_CIM_ConcreteJob_TimeBeforeRemoval,
};

/*[2072]*/
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

/*[2092]*/
const Meta_Class CIM_ConcreteJob::static_meta_class =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
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
    0,
};

CIMPLE_NAMESPACE_END

