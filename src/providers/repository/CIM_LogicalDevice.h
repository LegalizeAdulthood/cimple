//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_LogicalDevice_h
#define _cimple_CIM_LogicalDevice_h

#include <cimple/cimple.h>
#include "CIM_EnabledLogicalElement.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE CIM_LogicalDevice : public Instance
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

    CIMPLE_CLASS(CIM_LogicalDevice)
};

typedef CIM_EnabledLogicalElement_RequestStateChange_method CIM_LogicalDevice_RequestStateChange_method;

class CIMPLE_LINKAGE CIM_LogicalDevice_SetPowerState_method : public Instance
{
public:
    Property<uint16> PowerState;
    Property<Datetime> Time;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_SetPowerState_method)
};

class CIMPLE_LINKAGE CIM_LogicalDevice_Reset_method : public Instance
{
public:
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_Reset_method)
};

class CIMPLE_LINKAGE CIM_LogicalDevice_EnableDevice_method : public Instance
{
public:
    Property<boolean> Enabled;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_EnableDevice_method)
};

class CIMPLE_LINKAGE CIM_LogicalDevice_OnlineDevice_method : public Instance
{
public:
    Property<boolean> Online;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_OnlineDevice_method)
};

class CIMPLE_LINKAGE CIM_LogicalDevice_QuiesceDevice_method : public Instance
{
public:
    Property<boolean> Quiesce;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_QuiesceDevice_method)
};

class CIMPLE_LINKAGE CIM_LogicalDevice_SaveProperties_method : public Instance
{
public:
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_SaveProperties_method)
};

class CIMPLE_LINKAGE CIM_LogicalDevice_RestoreProperties_method : public Instance
{
public:
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_LogicalDevice_RestoreProperties_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_LogicalDevice_h */
