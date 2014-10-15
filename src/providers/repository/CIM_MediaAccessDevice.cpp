//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_MediaAccessDevice.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_11737B1039C317579F5467253A6F1AFD;

extern const Meta_Property _CIM_ManagedElement_Caption;

extern const Meta_Property _CIM_ManagedElement_Description;

extern const Meta_Property _CIM_ManagedElement_ElementName;

extern const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property _CIM_ManagedSystemElement_Name;

extern const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern const Meta_Property _CIM_ManagedSystemElement_Status;

extern const Meta_Property _CIM_EnabledLogicalElement_EnabledState;

extern const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState;

extern const Meta_Property _CIM_EnabledLogicalElement_RequestedState;

extern const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault;

extern const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange;

extern const Meta_Property _CIM_LogicalDevice_SystemCreationClassName;

extern const Meta_Property _CIM_LogicalDevice_SystemName;

extern const Meta_Property _CIM_LogicalDevice_CreationClassName;

extern const Meta_Property _CIM_LogicalDevice_DeviceID;

extern const Meta_Property _CIM_LogicalDevice_PowerManagementSupported;

extern const Meta_Property _CIM_LogicalDevice_PowerManagementCapabilities;

extern const Meta_Property _CIM_LogicalDevice_Availability;

extern const Meta_Property _CIM_LogicalDevice_StatusInfo;

extern const Meta_Property _CIM_LogicalDevice_LastErrorCode;

extern const Meta_Property _CIM_LogicalDevice_ErrorDescription;

extern const Meta_Property _CIM_LogicalDevice_ErrorCleared;

extern const Meta_Property _CIM_LogicalDevice_OtherIdentifyingInfo;

extern const Meta_Property _CIM_LogicalDevice_PowerOnHours;

extern const Meta_Property _CIM_LogicalDevice_TotalPowerOnHours;

extern const Meta_Property _CIM_LogicalDevice_IdentifyingDescriptions;

extern const Meta_Property _CIM_LogicalDevice_AdditionalAvailability;

extern const Meta_Property _CIM_LogicalDevice_MaxQuiesceTime;

extern const Meta_Property _CIM_MediaAccessDevice_Capabilities;

const Meta_Property _CIM_MediaAccessDevice_Capabilities =
{
    CIMPLE_FLAG_PROPERTY,
    "Capabilities",
    UINT16,
    -1,
    CIMPLE_OFF(CIM_MediaAccessDevice,Capabilities)
};

extern const Meta_Property _CIM_MediaAccessDevice_CapabilityDescriptions;

const Meta_Property _CIM_MediaAccessDevice_CapabilityDescriptions =
{
    CIMPLE_FLAG_PROPERTY,
    "CapabilityDescriptions",
    STRING,
    -1,
    CIMPLE_OFF(CIM_MediaAccessDevice,CapabilityDescriptions)
};

extern const Meta_Property _CIM_MediaAccessDevice_ErrorMethodology;

const Meta_Property _CIM_MediaAccessDevice_ErrorMethodology =
{
    CIMPLE_FLAG_PROPERTY,
    "ErrorMethodology",
    STRING,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,ErrorMethodology)
};

extern const Meta_Property _CIM_MediaAccessDevice_CompressionMethod;

const Meta_Property _CIM_MediaAccessDevice_CompressionMethod =
{
    CIMPLE_FLAG_PROPERTY,
    "CompressionMethod",
    STRING,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,CompressionMethod)
};

extern const Meta_Property _CIM_MediaAccessDevice_NumberOfMediaSupported;

const Meta_Property _CIM_MediaAccessDevice_NumberOfMediaSupported =
{
    CIMPLE_FLAG_PROPERTY,
    "NumberOfMediaSupported",
    UINT32,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,NumberOfMediaSupported)
};

extern const Meta_Property _CIM_MediaAccessDevice_MaxMediaSize;

const Meta_Property _CIM_MediaAccessDevice_MaxMediaSize =
{
    CIMPLE_FLAG_PROPERTY,
    "MaxMediaSize",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MaxMediaSize)
};

extern const Meta_Property _CIM_MediaAccessDevice_DefaultBlockSize;

const Meta_Property _CIM_MediaAccessDevice_DefaultBlockSize =
{
    CIMPLE_FLAG_PROPERTY,
    "DefaultBlockSize",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,DefaultBlockSize)
};

extern const Meta_Property _CIM_MediaAccessDevice_MaxBlockSize;

const Meta_Property _CIM_MediaAccessDevice_MaxBlockSize =
{
    CIMPLE_FLAG_PROPERTY,
    "MaxBlockSize",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MaxBlockSize)
};

extern const Meta_Property _CIM_MediaAccessDevice_MinBlockSize;

const Meta_Property _CIM_MediaAccessDevice_MinBlockSize =
{
    CIMPLE_FLAG_PROPERTY,
    "MinBlockSize",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MinBlockSize)
};

extern const Meta_Property _CIM_MediaAccessDevice_NeedsCleaning;

const Meta_Property _CIM_MediaAccessDevice_NeedsCleaning =
{
    CIMPLE_FLAG_PROPERTY,
    "NeedsCleaning",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,NeedsCleaning)
};

extern const Meta_Property _CIM_MediaAccessDevice_MediaIsLocked;

const Meta_Property _CIM_MediaAccessDevice_MediaIsLocked =
{
    CIMPLE_FLAG_PROPERTY,
    "MediaIsLocked",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MediaIsLocked)
};

extern const Meta_Property _CIM_MediaAccessDevice_Security;

const Meta_Property _CIM_MediaAccessDevice_Security =
{
    CIMPLE_FLAG_PROPERTY,
    "Security",
    UINT16,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,Security)
};

extern const Meta_Property _CIM_MediaAccessDevice_LastCleaned;

const Meta_Property _CIM_MediaAccessDevice_LastCleaned =
{
    CIMPLE_FLAG_PROPERTY,
    "LastCleaned",
    DATETIME,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,LastCleaned)
};

extern const Meta_Property _CIM_MediaAccessDevice_MaxAccessTime;

const Meta_Property _CIM_MediaAccessDevice_MaxAccessTime =
{
    CIMPLE_FLAG_PROPERTY,
    "MaxAccessTime",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MaxAccessTime)
};

extern const Meta_Property _CIM_MediaAccessDevice_UncompressedDataRate;

const Meta_Property _CIM_MediaAccessDevice_UncompressedDataRate =
{
    CIMPLE_FLAG_PROPERTY,
    "UncompressedDataRate",
    UINT32,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,UncompressedDataRate)
};

extern const Meta_Property _CIM_MediaAccessDevice_LoadTime;

const Meta_Property _CIM_MediaAccessDevice_LoadTime =
{
    CIMPLE_FLAG_PROPERTY,
    "LoadTime",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,LoadTime)
};

extern const Meta_Property _CIM_MediaAccessDevice_UnloadTime;

const Meta_Property _CIM_MediaAccessDevice_UnloadTime =
{
    CIMPLE_FLAG_PROPERTY,
    "UnloadTime",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,UnloadTime)
};

extern const Meta_Property _CIM_MediaAccessDevice_MountCount;

const Meta_Property _CIM_MediaAccessDevice_MountCount =
{
    CIMPLE_FLAG_PROPERTY,
    "MountCount",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MountCount)
};

extern const Meta_Property _CIM_MediaAccessDevice_TimeOfLastMount;

const Meta_Property _CIM_MediaAccessDevice_TimeOfLastMount =
{
    CIMPLE_FLAG_PROPERTY,
    "TimeOfLastMount",
    DATETIME,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,TimeOfLastMount)
};

extern const Meta_Property _CIM_MediaAccessDevice_TotalMountTime;

const Meta_Property _CIM_MediaAccessDevice_TotalMountTime =
{
    CIMPLE_FLAG_PROPERTY,
    "TotalMountTime",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,TotalMountTime)
};

extern const Meta_Property _CIM_MediaAccessDevice_UnitsDescription;

const Meta_Property _CIM_MediaAccessDevice_UnitsDescription =
{
    CIMPLE_FLAG_PROPERTY,
    "UnitsDescription",
    STRING,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,UnitsDescription)
};

extern const Meta_Property _CIM_MediaAccessDevice_MaxUnitsBeforeCleaning;

const Meta_Property _CIM_MediaAccessDevice_MaxUnitsBeforeCleaning =
{
    CIMPLE_FLAG_PROPERTY,
    "MaxUnitsBeforeCleaning",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,MaxUnitsBeforeCleaning)
};

extern const Meta_Property _CIM_MediaAccessDevice_UnitsUsed;

const Meta_Property _CIM_MediaAccessDevice_UnitsUsed =
{
    CIMPLE_FLAG_PROPERTY,
    "UnitsUsed",
    UINT64,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice,UnitsUsed)
};

static const Meta_Property _CIM_MediaAccessDevice_LockMedia_Lock =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Lock",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice_LockMedia_method,Lock)
};

static const Meta_Property _CIM_MediaAccessDevice_LockMedia_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(CIM_MediaAccessDevice_LockMedia_method,return_value)
};

static Meta_Feature* _CIM_MediaAccessDevice_LockMedia_meta_features[] =
{
    (Meta_Feature*)&_CIM_MediaAccessDevice_LockMedia_Lock,
    (Meta_Feature*)&_CIM_MediaAccessDevice_LockMedia_return_value
};

const Meta_Method CIM_MediaAccessDevice_LockMedia_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "LockMedia",
    _CIM_MediaAccessDevice_LockMedia_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_MediaAccessDevice_LockMedia_meta_features),
    sizeof(CIM_MediaAccessDevice_LockMedia_method),
    UINT32,
};

static Meta_Feature* _CIM_MediaAccessDevice_meta_features[] =
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

static const char* _super_classes[] =
{
    "CIM_LogicalDevice",
    "CIM_EnabledLogicalElement",
    "CIM_LogicalElement",
    "CIM_ManagedSystemElement",
    "CIM_ManagedElement",
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

const Meta_Class CIM_MediaAccessDevice::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_MediaAccessDevice",
    _CIM_MediaAccessDevice_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_MediaAccessDevice_meta_features),
    sizeof(CIM_MediaAccessDevice),
    _locals,
    &CIM_LogicalDevice::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    4, /* num_keys */
    0x2961C797,/* crc */
    &__meta_repository_11737B1039C317579F5467253A6F1AFD,
};

CIMPLE_NAMESPACE_END

