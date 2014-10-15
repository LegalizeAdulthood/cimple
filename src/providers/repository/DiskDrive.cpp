//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "DiskDrive.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedElement_Caption;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedElement_Description;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedElement_ElementName;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedSystemElement_InstallDate;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedSystemElement_Name;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

CIMPLE_HIDE
extern const Meta_Property _CIM_ManagedSystemElement_Status;

CIMPLE_HIDE
extern const Meta_Property _CIM_EnabledLogicalElement_EnabledState;

CIMPLE_HIDE
extern const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState;

CIMPLE_HIDE
extern const Meta_Property _CIM_EnabledLogicalElement_RequestedState;

CIMPLE_HIDE
extern const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault;

CIMPLE_HIDE
extern const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_SystemCreationClassName;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_SystemName;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_CreationClassName;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_DeviceID;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_PowerManagementSupported;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_PowerManagementCapabilities;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_Availability;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_StatusInfo;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_LastErrorCode;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_ErrorDescription;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_ErrorCleared;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_OtherIdentifyingInfo;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_PowerOnHours;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_TotalPowerOnHours;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_IdentifyingDescriptions;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_AdditionalAvailability;

CIMPLE_HIDE
extern const Meta_Property _CIM_LogicalDevice_MaxQuiesceTime;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_Capabilities;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_CapabilityDescriptions;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_ErrorMethodology;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_CompressionMethod;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_NumberOfMediaSupported;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MaxMediaSize;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_DefaultBlockSize;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MaxBlockSize;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MinBlockSize;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_NeedsCleaning;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MediaIsLocked;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_Security;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_LastCleaned;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MaxAccessTime;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_UncompressedDataRate;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_LoadTime;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_UnloadTime;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MountCount;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_TimeOfLastMount;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_TotalMountTime;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_UnitsDescription;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_MaxUnitsBeforeCleaning;

CIMPLE_HIDE
extern const Meta_Property _CIM_MediaAccessDevice_UnitsUsed;

static Meta_Feature* _DiskDrive_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Name,
    (Meta_Feature*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_EnabledState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_OtherEnabledState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestedState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_EnabledDefault,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_TimeOfLastStateChange,
    (Meta_Feature*)&CIM_EnabledLogicalElement_RequestStateChange_method::static_meta_class,
    (Meta_Feature*)&_CIM_LogicalDevice_SystemCreationClassName,
    (Meta_Feature*)&_CIM_LogicalDevice_SystemName,
    (Meta_Feature*)&_CIM_LogicalDevice_CreationClassName,
    (Meta_Feature*)&_CIM_LogicalDevice_DeviceID,
    (Meta_Feature*)&_CIM_LogicalDevice_PowerManagementSupported,
    (Meta_Feature*)&_CIM_LogicalDevice_PowerManagementCapabilities,
    (Meta_Feature*)&_CIM_LogicalDevice_Availability,
    (Meta_Feature*)&_CIM_LogicalDevice_StatusInfo,
    (Meta_Feature*)&_CIM_LogicalDevice_LastErrorCode,
    (Meta_Feature*)&_CIM_LogicalDevice_ErrorDescription,
    (Meta_Feature*)&_CIM_LogicalDevice_ErrorCleared,
    (Meta_Feature*)&_CIM_LogicalDevice_OtherIdentifyingInfo,
    (Meta_Feature*)&_CIM_LogicalDevice_PowerOnHours,
    (Meta_Feature*)&_CIM_LogicalDevice_TotalPowerOnHours,
    (Meta_Feature*)&_CIM_LogicalDevice_IdentifyingDescriptions,
    (Meta_Feature*)&_CIM_LogicalDevice_AdditionalAvailability,
    (Meta_Feature*)&_CIM_LogicalDevice_MaxQuiesceTime,
    (Meta_Feature*)&CIM_LogicalDevice_SetPowerState_method::static_meta_class,
    (Meta_Feature*)&CIM_LogicalDevice_Reset_method::static_meta_class,
    (Meta_Feature*)&CIM_LogicalDevice_EnableDevice_method::static_meta_class,
    (Meta_Feature*)&CIM_LogicalDevice_OnlineDevice_method::static_meta_class,
    (Meta_Feature*)&CIM_LogicalDevice_QuiesceDevice_method::static_meta_class,
    (Meta_Feature*)&CIM_LogicalDevice_SaveProperties_method::static_meta_class,
    (Meta_Feature*)&CIM_LogicalDevice_RestoreProperties_method::static_meta_class,
    (Meta_Feature*)&_CIM_MediaAccessDevice_Capabilities,
    (Meta_Feature*)&_CIM_MediaAccessDevice_CapabilityDescriptions,
    (Meta_Feature*)&_CIM_MediaAccessDevice_ErrorMethodology,
    (Meta_Feature*)&_CIM_MediaAccessDevice_CompressionMethod,
    (Meta_Feature*)&_CIM_MediaAccessDevice_NumberOfMediaSupported,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MaxMediaSize,
    (Meta_Feature*)&_CIM_MediaAccessDevice_DefaultBlockSize,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MaxBlockSize,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MinBlockSize,
    (Meta_Feature*)&_CIM_MediaAccessDevice_NeedsCleaning,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MediaIsLocked,
    (Meta_Feature*)&_CIM_MediaAccessDevice_Security,
    (Meta_Feature*)&_CIM_MediaAccessDevice_LastCleaned,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MaxAccessTime,
    (Meta_Feature*)&_CIM_MediaAccessDevice_UncompressedDataRate,
    (Meta_Feature*)&_CIM_MediaAccessDevice_LoadTime,
    (Meta_Feature*)&_CIM_MediaAccessDevice_UnloadTime,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MountCount,
    (Meta_Feature*)&_CIM_MediaAccessDevice_TimeOfLastMount,
    (Meta_Feature*)&_CIM_MediaAccessDevice_TotalMountTime,
    (Meta_Feature*)&_CIM_MediaAccessDevice_UnitsDescription,
    (Meta_Feature*)&_CIM_MediaAccessDevice_MaxUnitsBeforeCleaning,
    (Meta_Feature*)&_CIM_MediaAccessDevice_UnitsUsed,
    (Meta_Feature*)&CIM_MediaAccessDevice_LockMedia_method::static_meta_class,
};

const Meta_Class DiskDrive::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "DiskDrive",
    _DiskDrive_meta_features,
    CIMPLE_ARRAY_SIZE(_DiskDrive_meta_features),
    sizeof(DiskDrive),
    &CIM_DiskDrive::static_meta_class,
    4,
    0x46EE00ED,
};

CIMPLE_NAMESPACE_END

