/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_Job.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_51B6701FC40818A399B7D3CB5CC114A4;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property
_CIM_ManagedSystemElement_Name;

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

const Meta_Property
_CIM_Job_JobStatus =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "JobStatus",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,JobStatus),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_TimeSubmitted;

const Meta_Property
_CIM_Job_TimeSubmitted =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TimeSubmitted",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,TimeSubmitted),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_ScheduledStartTime;

const Meta_Property
_CIM_Job_ScheduledStartTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "ScheduledStartTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,ScheduledStartTime),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_StartTime;

const Meta_Property
_CIM_Job_StartTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "StartTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,StartTime),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_ElapsedTime;

const Meta_Property
_CIM_Job_ElapsedTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ElapsedTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,ElapsedTime),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_JobRunTimes;

static const Meta_Value_Scalar<uint32>
_CIM_Job_JobRunTimes_MV =
{
    1
};

const Meta_Property
_CIM_Job_JobRunTimes =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "JobRunTimes",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,JobRunTimes),
    (const Meta_Value*)(void*)&_CIM_Job_JobRunTimes_MV,
};

extern const Meta_Property
_CIM_Job_RunMonth;

const Meta_Property
_CIM_Job_RunMonth =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "RunMonth",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT8,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,RunMonth),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_RunDay;

const Meta_Property
_CIM_Job_RunDay =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "RunDay",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    SINT8,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,RunDay),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_RunDayOfWeek;

const Meta_Property
_CIM_Job_RunDayOfWeek =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "RunDayOfWeek",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    SINT8,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,RunDayOfWeek),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_RunStartInterval;

const Meta_Property
_CIM_Job_RunStartInterval =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "RunStartInterval",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,RunStartInterval),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_LocalOrUtcTime;

const Meta_Property
_CIM_Job_LocalOrUtcTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "LocalOrUtcTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,LocalOrUtcTime),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_UntilTime;

const Meta_Property
_CIM_Job_UntilTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "UntilTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,UntilTime),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_Notify;

const Meta_Property
_CIM_Job_Notify =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "Notify",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,Notify),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_Owner;

const Meta_Property
_CIM_Job_Owner =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Owner",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,Owner),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_Priority;

const Meta_Property
_CIM_Job_Priority =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "Priority",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,Priority),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_PercentComplete;

const Meta_Property
_CIM_Job_PercentComplete =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "PercentComplete",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,PercentComplete),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_DeleteOnCompletion;

const Meta_Property
_CIM_Job_DeleteOnCompletion =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "DeleteOnCompletion",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,DeleteOnCompletion),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_ErrorCode;

const Meta_Property
_CIM_Job_ErrorCode =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ErrorCode",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,ErrorCode),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_ErrorDescription;

const Meta_Property
_CIM_Job_ErrorDescription =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ErrorDescription",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,ErrorDescription),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_RecoveryAction;

const Meta_Property
_CIM_Job_RecoveryAction =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "RecoveryAction",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,RecoveryAction),
    0, /* value */
};

extern const Meta_Property
_CIM_Job_OtherRecoveryAction;

const Meta_Property
_CIM_Job_OtherRecoveryAction =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherRecoveryAction",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Job,OtherRecoveryAction),
    0, /* value */
};

static const Meta_Property
_CIM_Job_KillJob_DeleteOnKill =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "DeleteOnKill",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_Job_KillJob_method,DeleteOnKill),
    0, /* value */
};

static const Meta_Property
_CIM_Job_KillJob_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_Job_KillJob_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_Job_KillJob_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_Job_KillJob_DeleteOnKill,
    (Meta_Feature*)(void*)&_CIM_Job_KillJob_return_value
};

const Meta_Method
CIM_Job_KillJob_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "KillJob",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_Job_KillJob_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_Job_KillJob_MFA),
    sizeof(CIM_Job_KillJob_method),
    UINT32,
};

static Meta_Feature* _CIM_Job_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_Name,
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
};

static const Meta_Feature_Local _locals[] =
{
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
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_Job::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_Job",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_Job_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_Job_MFA),
    sizeof(CIM_Job),
    _locals,
    &CIM_LogicalElement::static_meta_class,
    0, /* num_keys */
    &__meta_repository_51B6701FC40818A399B7D3CB5CC114A4,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/CIM_DiskDrive/CIM_Job.cpp,v 1.7 2007/04/26 22:41:00 mbrasher-public Exp $");
