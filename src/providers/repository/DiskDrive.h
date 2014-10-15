//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_DiskDrive_h
#define _cimple_DiskDrive_h

#include <cimple/cimple.h>
#include "CIM_DiskDrive.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE DiskDrive : public Instance
{
public:
    // CIM_ManagedElement features:
    Property<String> Caption;
    Property<String> Description;
    Property<String> ElementName;

    // CIM_ManagedSystemElement features:
    Property<Datetime> InstallDate;
    Property<String> Name;
    Property<Array_uint16> OperationalStatus;
    Property<Array_String> StatusDescriptions;
    Property<String> Status;

    // CIM_LogicalElement features:

    // CIM_EnabledLogicalElement features:
    Property<uint16> EnabledState;
    Property<String> OtherEnabledState;
    Property<uint16> RequestedState;
    Property<uint16> EnabledDefault;
    Property<Datetime> TimeOfLastStateChange;

    // CIM_LogicalDevice features:
    Property<String> SystemCreationClassName;
    Property<String> SystemName;
    Property<String> CreationClassName;
    Property<String> DeviceID;
    Property<boolean> PowerManagementSupported;
    Property<Array_uint16> PowerManagementCapabilities;
    Property<uint16> Availability;
    Property<uint16> StatusInfo;
    Property<uint32> LastErrorCode;
    Property<String> ErrorDescription;
    Property<boolean> ErrorCleared;
    Property<Array_String> OtherIdentifyingInfo;
    Property<uint64> PowerOnHours;
    Property<uint64> TotalPowerOnHours;
    Property<Array_String> IdentifyingDescriptions;
    Property<Array_uint16> AdditionalAvailability;
    Property<uint64> MaxQuiesceTime;

    // CIM_MediaAccessDevice features:
    Property<Array_uint16> Capabilities;
    Property<Array_String> CapabilityDescriptions;
    Property<String> ErrorMethodology;
    Property<String> CompressionMethod;
    Property<uint32> NumberOfMediaSupported;
    Property<uint64> MaxMediaSize;
    Property<uint64> DefaultBlockSize;
    Property<uint64> MaxBlockSize;
    Property<uint64> MinBlockSize;
    Property<boolean> NeedsCleaning;
    Property<boolean> MediaIsLocked;
    Property<uint16> Security;
    Property<Datetime> LastCleaned;
    Property<uint64> MaxAccessTime;
    Property<uint32> UncompressedDataRate;
    Property<uint64> LoadTime;
    Property<uint64> UnloadTime;
    Property<uint64> MountCount;
    Property<Datetime> TimeOfLastMount;
    Property<uint64> TotalMountTime;
    Property<String> UnitsDescription;
    Property<uint64> MaxUnitsBeforeCleaning;
    Property<uint64> UnitsUsed;

    // CIM_DiskDrive features:

    // DiskDrive features:

    CIMPLE_CLASS(DiskDrive)
};

typedef CIM_EnabledLogicalElement_RequestStateChange_method DiskDrive_RequestStateChange_method;

typedef CIM_LogicalDevice_SetPowerState_method DiskDrive_SetPowerState_method;

typedef CIM_LogicalDevice_Reset_method DiskDrive_Reset_method;

typedef CIM_LogicalDevice_EnableDevice_method DiskDrive_EnableDevice_method;

typedef CIM_LogicalDevice_OnlineDevice_method DiskDrive_OnlineDevice_method;

typedef CIM_LogicalDevice_QuiesceDevice_method DiskDrive_QuiesceDevice_method;

typedef CIM_LogicalDevice_SaveProperties_method DiskDrive_SaveProperties_method;

typedef CIM_LogicalDevice_RestoreProperties_method DiskDrive_RestoreProperties_method;

typedef CIM_MediaAccessDevice_LockMedia_method DiskDrive_LockMedia_method;

CIMPLE_NAMESPACE_END

#endif /* _cimple_DiskDrive_h */
