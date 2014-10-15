/*NOCHKSRC*/
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

extern const Meta_Repository __meta_repository_F4A795C4F3BC1F5C8B8959AFA40EE849;

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
_CIM_MediaAccessDevice_Capabilities;

extern const Meta_Property
_CIM_MediaAccessDevice_CapabilityDescriptions;

extern const Meta_Property
_CIM_MediaAccessDevice_ErrorMethodology;

extern const Meta_Property
_CIM_MediaAccessDevice_CompressionMethod;

extern const Meta_Property
_CIM_MediaAccessDevice_NumberOfMediaSupported;

extern const Meta_Property
_CIM_MediaAccessDevice_MaxMediaSize;

extern const Meta_Property
_CIM_MediaAccessDevice_DefaultBlockSize;

extern const Meta_Property
_CIM_MediaAccessDevice_MaxBlockSize;

extern const Meta_Property
_CIM_MediaAccessDevice_MinBlockSize;

extern const Meta_Property
_CIM_MediaAccessDevice_NeedsCleaning;

extern const Meta_Property
_CIM_MediaAccessDevice_MediaIsLocked;

extern const Meta_Property
_CIM_MediaAccessDevice_Security;

extern const Meta_Property
_CIM_MediaAccessDevice_LastCleaned;

extern const Meta_Property
_CIM_MediaAccessDevice_MaxAccessTime;

extern const Meta_Property
_CIM_MediaAccessDevice_UncompressedDataRate;

extern const Meta_Property
_CIM_MediaAccessDevice_LoadTime;

extern const Meta_Property
_CIM_MediaAccessDevice_UnloadTime;

extern const Meta_Property
_CIM_MediaAccessDevice_MountCount;

extern const Meta_Property
_CIM_MediaAccessDevice_TimeOfLastMount;

extern const Meta_Property
_CIM_MediaAccessDevice_TotalMountTime;

extern const Meta_Property
_CIM_MediaAccessDevice_UnitsDescription;

extern const Meta_Property
_CIM_MediaAccessDevice_MaxUnitsBeforeCleaning;

extern const Meta_Property
_CIM_MediaAccessDevice_UnitsUsed;

static Meta_Feature* _DiskDrive_MFA[] =
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
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
};

const Meta_Class DiskDrive::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "DiskDrive",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _DiskDrive_MFA,
    CIMPLE_ARRAY_SIZE(_DiskDrive_MFA),
    sizeof(DiskDrive),
    _locals,
    &CIM_DiskDrive::static_meta_class,
    4, /* num_keys */
    0x46EE00ED, /* crc */
    &__meta_repository_F4A795C4F3BC1F5C8B8959AFA40EE849,
};

CIMPLE_NAMESPACE_END

