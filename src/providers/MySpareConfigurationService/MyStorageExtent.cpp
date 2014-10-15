/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "MyStorageExtent.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_C2AA78B37C6515EB9DBF2BC150C67E7F;

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

extern const Meta_Property
_CIM_StorageExtent_Purpose;

extern const Meta_Property
_CIM_StorageExtent_Access;

extern const Meta_Property
_CIM_StorageExtent_ErrorMethodology;

extern const Meta_Property
_CIM_StorageExtent_BlockSize;

extern const Meta_Property
_CIM_StorageExtent_NumberOfBlocks;

extern const Meta_Property
_CIM_StorageExtent_ConsumableBlocks;

extern const Meta_Property
_CIM_StorageExtent_IsBasedOnUnderlyingRedundancy;

extern const Meta_Property
_CIM_StorageExtent_SequentialAccess;

extern const Meta_Property
_CIM_StorageExtent_ExtentStatus;

extern const Meta_Property
_CIM_StorageExtent_NoSinglePointOfFailure;

extern const Meta_Property
_CIM_StorageExtent_DataRedundancy;

extern const Meta_Property
_CIM_StorageExtent_PackageRedundancy;

extern const Meta_Property
_CIM_StorageExtent_DeltaReservation;

extern const Meta_Property
_CIM_StorageExtent_Primordial;

static Meta_Feature* _MyStorageExtent_MFA[] =
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
};

const Meta_Class MyStorageExtent::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "MyStorageExtent",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _MyStorageExtent_MFA,
    CIMPLE_ARRAY_SIZE(_MyStorageExtent_MFA),
    sizeof(MyStorageExtent),
    _locals,
    &CIM_StorageExtent::static_meta_class,
    4, /* num_keys */
    0x155B6ED9, /* crc */
    &__meta_repository_C2AA78B37C6515EB9DBF2BC150C67E7F,
};

CIMPLE_NAMESPACE_END

