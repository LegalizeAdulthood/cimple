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

extern const Meta_Repository __meta_repository_301C3D768E5D1704B1028C1944B9CD9D;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Caption;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Description;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_ElementName;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_Name;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_Status;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_RequestedState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_SystemCreationClassName;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_SystemName;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_CreationClassName;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_DeviceID;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_PowerManagementSupported;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_PowerManagementCapabilities;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_Availability;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_StatusInfo;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_LastErrorCode;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_ErrorDescription;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_ErrorCleared;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_OtherIdentifyingInfo;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_PowerOnHours;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_TotalPowerOnHours;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_IdentifyingDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_AdditionalAvailability;

extern CIMPLE_HIDE const Meta_Property _CIM_LogicalDevice_MaxQuiesceTime;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_Capabilities;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_CapabilityDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_ErrorMethodology;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_CompressionMethod;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_NumberOfMediaSupported;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MaxMediaSize;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_DefaultBlockSize;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MaxBlockSize;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MinBlockSize;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_NeedsCleaning;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MediaIsLocked;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_Security;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_LastCleaned;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MaxAccessTime;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_UncompressedDataRate;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_LoadTime;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_UnloadTime;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MountCount;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_TimeOfLastMount;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_TotalMountTime;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_UnitsDescription;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_MaxUnitsBeforeCleaning;

extern CIMPLE_HIDE const Meta_Property _CIM_MediaAccessDevice_UnitsUsed;

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
    &__meta_repository_301C3D768E5D1704B1028C1944B9CD9D,
};

CIMPLE_NAMESPACE_END

