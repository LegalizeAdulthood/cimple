/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_StorageExtent.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_8CCF8E58804E17C2BA75EC619FBC3236;

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

extern const Meta_Property
_CIM_LogicalDevice_SystemName;

extern const Meta_Property
_CIM_LogicalDevice_CreationClassName;

extern const Meta_Property
_CIM_LogicalDevice_DeviceID;

extern const Meta_Property
_CIM_LogicalDevice_PowerManagementSupported;

extern const Meta_Property
_CIM_LogicalDevice_PowerManagementCapabilities;

extern const Meta_Property
_CIM_LogicalDevice_Availability;

extern const Meta_Property
_CIM_LogicalDevice_StatusInfo;

extern const Meta_Property
_CIM_LogicalDevice_LastErrorCode;

extern const Meta_Property
_CIM_LogicalDevice_ErrorDescription;

extern const Meta_Property
_CIM_LogicalDevice_ErrorCleared;

extern const Meta_Property
_CIM_LogicalDevice_OtherIdentifyingInfo;

extern const Meta_Property
_CIM_LogicalDevice_PowerOnHours;

extern const Meta_Property
_CIM_LogicalDevice_TotalPowerOnHours;

extern const Meta_Property
_CIM_LogicalDevice_IdentifyingDescriptions;

extern const Meta_Property
_CIM_LogicalDevice_AdditionalAvailability;

extern const Meta_Property
_CIM_LogicalDevice_MaxQuiesceTime;

extern const Meta_Property
_CIM_StorageExtent_DataOrganization;

const Meta_Property
_CIM_StorageExtent_DataOrganization =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "DataOrganization",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,DataOrganization),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_Purpose;

const Meta_Property
_CIM_StorageExtent_Purpose =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Purpose",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,Purpose),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_Access;

const Meta_Property
_CIM_StorageExtent_Access =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Access",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,Access),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_ErrorMethodology;

const Meta_Property
_CIM_StorageExtent_ErrorMethodology =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ErrorMethodology",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,ErrorMethodology),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_BlockSize;

const Meta_Property
_CIM_StorageExtent_BlockSize =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "BlockSize",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,BlockSize),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_NumberOfBlocks;

const Meta_Property
_CIM_StorageExtent_NumberOfBlocks =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "NumberOfBlocks",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,NumberOfBlocks),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_ConsumableBlocks;

const Meta_Property
_CIM_StorageExtent_ConsumableBlocks =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConsumableBlocks",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,ConsumableBlocks),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_IsBasedOnUnderlyingRedundancy;

const Meta_Property
_CIM_StorageExtent_IsBasedOnUnderlyingRedundancy =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "IsBasedOnUnderlyingRedundancy",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,IsBasedOnUnderlyingRedundancy),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_SequentialAccess;

const Meta_Property
_CIM_StorageExtent_SequentialAccess =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "SequentialAccess",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,SequentialAccess),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_ExtentStatus;

const Meta_Property
_CIM_StorageExtent_ExtentStatus =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ExtentStatus",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,ExtentStatus),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_NoSinglePointOfFailure;

const Meta_Property
_CIM_StorageExtent_NoSinglePointOfFailure =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "NoSinglePointOfFailure",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,NoSinglePointOfFailure),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_DataRedundancy;

const Meta_Property
_CIM_StorageExtent_DataRedundancy =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "DataRedundancy",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,DataRedundancy),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_PackageRedundancy;

const Meta_Property
_CIM_StorageExtent_PackageRedundancy =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "PackageRedundancy",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,PackageRedundancy),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_DeltaReservation;

const Meta_Property
_CIM_StorageExtent_DeltaReservation =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "DeltaReservation",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT8,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,DeltaReservation),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageExtent_Primordial;

static const Meta_Value_Scalar<boolean>
_CIM_StorageExtent_Primordial_MV =
{
    false
};

const Meta_Property
_CIM_StorageExtent_Primordial =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Primordial",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageExtent,Primordial),
    (const Meta_Value*)(void*)&_CIM_StorageExtent_Primordial_MV,
};

static Meta_Feature* _CIM_StorageExtent_MFA[] =
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
    (Meta_Feature*)(void*)&_CIM_StorageExtent_DataOrganization,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_Purpose,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_Access,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_ErrorMethodology,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_BlockSize,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_NumberOfBlocks,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_ConsumableBlocks,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_IsBasedOnUnderlyingRedundancy,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_SequentialAccess,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_ExtentStatus,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_NoSinglePointOfFailure,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_DataRedundancy,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_PackageRedundancy,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_DeltaReservation,
    (Meta_Feature*)(void*)&_CIM_StorageExtent_Primordial,
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

const Meta_Class CIM_StorageExtent::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_StorageExtent",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_StorageExtent_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_StorageExtent_MFA),
    sizeof(CIM_StorageExtent),
    _locals,
    &CIM_LogicalDevice::static_meta_class,
    4, /* num_keys */
    0x9C054652, /* crc */
    &__meta_repository_8CCF8E58804E17C2BA75EC619FBC3236,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/SNIA_SpareConfigurationService/CIM_StorageExtent.cpp,v 1.9 2007/04/18 03:29:41 mbrasher-public Exp $");
