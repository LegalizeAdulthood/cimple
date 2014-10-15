/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_LogicalDevice.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_0534992289351A029B38A12919E776DE;

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
_CIM_EnabledLogicalElement_EnabledState;

extern const Meta_Property
_CIM_EnabledLogicalElement_OtherEnabledState;

extern const Meta_Property
_CIM_EnabledLogicalElement_RequestedState;

extern const Meta_Property
_CIM_EnabledLogicalElement_EnabledDefault;

extern const Meta_Property
_CIM_EnabledLogicalElement_TimeOfLastStateChange;

extern const Meta_Property
_CIM_LogicalDevice_SystemCreationClassName;

const Meta_Property
_CIM_LogicalDevice_SystemCreationClassName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "SystemCreationClassName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,SystemCreationClassName),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_SystemName;

const Meta_Property
_CIM_LogicalDevice_SystemName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "SystemName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,SystemName),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_CreationClassName;

const Meta_Property
_CIM_LogicalDevice_CreationClassName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "CreationClassName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,CreationClassName),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_DeviceID;

const Meta_Property
_CIM_LogicalDevice_DeviceID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "DeviceID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,DeviceID),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_PowerManagementSupported;

const Meta_Property
_CIM_LogicalDevice_PowerManagementSupported =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "PowerManagementSupported",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,PowerManagementSupported),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_PowerManagementCapabilities;

const Meta_Property
_CIM_LogicalDevice_PowerManagementCapabilities =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "PowerManagementCapabilities",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,PowerManagementCapabilities),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_Availability;

const Meta_Property
_CIM_LogicalDevice_Availability =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Availability",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,Availability),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_StatusInfo;

const Meta_Property
_CIM_LogicalDevice_StatusInfo =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "StatusInfo",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,StatusInfo),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_LastErrorCode;

const Meta_Property
_CIM_LogicalDevice_LastErrorCode =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "LastErrorCode",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,LastErrorCode),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_ErrorDescription;

const Meta_Property
_CIM_LogicalDevice_ErrorDescription =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ErrorDescription",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,ErrorDescription),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_ErrorCleared;

const Meta_Property
_CIM_LogicalDevice_ErrorCleared =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ErrorCleared",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,ErrorCleared),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_OtherIdentifyingInfo;

const Meta_Property
_CIM_LogicalDevice_OtherIdentifyingInfo =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherIdentifyingInfo",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,OtherIdentifyingInfo),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_PowerOnHours;

const Meta_Property
_CIM_LogicalDevice_PowerOnHours =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_COUNTER|CIMPLE_FLAG_READ,
    "PowerOnHours",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,PowerOnHours),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_TotalPowerOnHours;

const Meta_Property
_CIM_LogicalDevice_TotalPowerOnHours =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_COUNTER|CIMPLE_FLAG_READ,
    "TotalPowerOnHours",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,TotalPowerOnHours),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_IdentifyingDescriptions;

const Meta_Property
_CIM_LogicalDevice_IdentifyingDescriptions =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "IdentifyingDescriptions",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,IdentifyingDescriptions),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_AdditionalAvailability;

const Meta_Property
_CIM_LogicalDevice_AdditionalAvailability =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "AdditionalAvailability",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,AdditionalAvailability),
    0, /* value */
};

extern const Meta_Property
_CIM_LogicalDevice_MaxQuiesceTime;

const Meta_Property
_CIM_LogicalDevice_MaxQuiesceTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "MaxQuiesceTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_LogicalDevice,MaxQuiesceTime),
    0, /* value */
};

static const Meta_Property
_CIM_LogicalDevice_SetPowerState_PowerState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "PowerState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_SetPowerState_method,PowerState),
    0, /* value */
};

static const Meta_Property
_CIM_LogicalDevice_SetPowerState_Time =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Time",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_SetPowerState_method,Time),
    0, /* value */
};

static const Meta_Property
_CIM_LogicalDevice_SetPowerState_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_SetPowerState_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_SetPowerState_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_SetPowerState_PowerState,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_SetPowerState_Time,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_SetPowerState_return_value
};

const Meta_Method
CIM_LogicalDevice_SetPowerState_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "SetPowerState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_SetPowerState_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_SetPowerState_MFA),
    sizeof(CIM_LogicalDevice_SetPowerState_method),
    UINT32,
};

static const Meta_Property
_CIM_LogicalDevice_Reset_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_Reset_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_Reset_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_Reset_return_value
};

const Meta_Method
CIM_LogicalDevice_Reset_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "Reset",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_Reset_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_Reset_MFA),
    sizeof(CIM_LogicalDevice_Reset_method),
    UINT32,
};

static const Meta_Property
_CIM_LogicalDevice_EnableDevice_Enabled =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Enabled",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_EnableDevice_method,Enabled),
    0, /* value */
};

static const Meta_Property
_CIM_LogicalDevice_EnableDevice_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_EnableDevice_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_EnableDevice_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_EnableDevice_Enabled,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_EnableDevice_return_value
};

const Meta_Method
CIM_LogicalDevice_EnableDevice_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "EnableDevice",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_EnableDevice_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_EnableDevice_MFA),
    sizeof(CIM_LogicalDevice_EnableDevice_method),
    UINT32,
};

static const Meta_Property
_CIM_LogicalDevice_OnlineDevice_Online =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Online",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_OnlineDevice_method,Online),
    0, /* value */
};

static const Meta_Property
_CIM_LogicalDevice_OnlineDevice_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_OnlineDevice_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_OnlineDevice_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_OnlineDevice_Online,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_OnlineDevice_return_value
};

const Meta_Method
CIM_LogicalDevice_OnlineDevice_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "OnlineDevice",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_OnlineDevice_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_OnlineDevice_MFA),
    sizeof(CIM_LogicalDevice_OnlineDevice_method),
    UINT32,
};

static const Meta_Property
_CIM_LogicalDevice_QuiesceDevice_Quiesce =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Quiesce",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_QuiesceDevice_method,Quiesce),
    0, /* value */
};

static const Meta_Property
_CIM_LogicalDevice_QuiesceDevice_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_QuiesceDevice_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_QuiesceDevice_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_QuiesceDevice_Quiesce,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_QuiesceDevice_return_value
};

const Meta_Method
CIM_LogicalDevice_QuiesceDevice_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "QuiesceDevice",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_QuiesceDevice_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_QuiesceDevice_MFA),
    sizeof(CIM_LogicalDevice_QuiesceDevice_method),
    UINT32,
};

static const Meta_Property
_CIM_LogicalDevice_SaveProperties_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_SaveProperties_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_SaveProperties_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_SaveProperties_return_value
};

const Meta_Method
CIM_LogicalDevice_SaveProperties_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "SaveProperties",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_SaveProperties_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_SaveProperties_MFA),
    sizeof(CIM_LogicalDevice_SaveProperties_method),
    UINT32,
};

static const Meta_Property
_CIM_LogicalDevice_RestoreProperties_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_LogicalDevice_RestoreProperties_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_LogicalDevice_RestoreProperties_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_RestoreProperties_return_value
};

const Meta_Method
CIM_LogicalDevice_RestoreProperties_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "RestoreProperties",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_RestoreProperties_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_RestoreProperties_MFA),
    sizeof(CIM_LogicalDevice_RestoreProperties_method),
    UINT32,
};

static Meta_Feature* _CIM_LogicalDevice_MFA[] =
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
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_EnabledState,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_OtherEnabledState,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_RequestedState,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_EnabledDefault,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_TimeOfLastStateChange,
    (Meta_Feature*)(void*)&CIM_EnabledLogicalElement_RequestStateChange_method::static_meta_class,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_SystemCreationClassName,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_SystemName,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_CreationClassName,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_DeviceID,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_PowerManagementSupported,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_PowerManagementCapabilities,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_Availability,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_StatusInfo,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_LastErrorCode,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_ErrorDescription,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_ErrorCleared,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_OtherIdentifyingInfo,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_PowerOnHours,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_TotalPowerOnHours,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_IdentifyingDescriptions,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_AdditionalAvailability,
    (Meta_Feature*)(void*)&_CIM_LogicalDevice_MaxQuiesceTime,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_SetPowerState_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_Reset_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_EnableDevice_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_OnlineDevice_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_QuiesceDevice_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_SaveProperties_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_LogicalDevice_RestoreProperties_method::static_meta_class,
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
    {1},
    {1},
};

const Meta_Class CIM_LogicalDevice::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_LogicalDevice",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalDevice_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalDevice_MFA),
    sizeof(CIM_LogicalDevice),
    _locals,
    &CIM_EnabledLogicalElement::static_meta_class,
    4, /* num_keys */
    &__meta_repository_0534992289351A029B38A12919E776DE,
};

CIMPLE_NAMESPACE_END

