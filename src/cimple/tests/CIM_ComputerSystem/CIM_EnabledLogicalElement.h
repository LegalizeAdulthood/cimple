/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_EnabledLogicalElement_h
#define _cimple_CIM_EnabledLogicalElement_h

#include <cimple/cimple.h>
#include "CIM_LogicalElement.h"
#include "CIM_ConcreteJob.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_EnabledLogicalElement : public Instance
{
public:
    // CIM_ManagedElement features:
    Property<String> Caption;
    Property<String> Description;
    Property<String> ElementName;

    // CIM_ManagedSystemElement features:
    Property<Datetime> InstallDate;
    Property<String> Name;
    struct _OperationalStatus
    {
        enum
        {
            enum_Unknown = 0,
            enum_Other = 1,
            enum_OK = 2,
            enum_Degraded = 3,
            enum_Stressed = 4,
            enum_Predictive_Failure = 5,
            enum_Error = 6,
            enum_Non_Recoverable_Error = 7,
            enum_Starting = 8,
            enum_Stopping = 9,
            enum_Stopped = 10,
            enum_In_Service = 11,
            enum_No_Contact = 12,
            enum_Lost_Communication = 13,
            enum_Aborted = 14,
            enum_Dormant = 15,
            enum_Supporting_Entity_in_Error = 16,
            enum_Completed = 17,
            enum_Power_Mode = 18,
            enum_DMTF_Reserved = 0,
            enum_Vendor_Reserved = 0,
        };
        Array_uint16 value;
        uint8 null;
    }
    OperationalStatus;
    Property<Array_String> StatusDescriptions;
    Property<String> Status;
    struct _HealthState
    {
        enum
        {
            enum_Unknown = 0,
            enum_OK = 5,
            enum_Degraded_Warning = 10,
            enum_Minor_failure = 15,
            enum_Major_failure = 20,
            enum_Critical_failure = 25,
            enum_Non_recoverable_error = 30,
            enum_DMTF_Reserved = 0,
        };
        uint16 value;
        uint8 null;
    }
    HealthState;

    // CIM_LogicalElement features:

    // CIM_EnabledLogicalElement features:
    struct _EnabledState
    {
        enum
        {
            enum_Unknown = 0,
            enum_Other = 1,
            enum_Enabled = 2,
            enum_Disabled = 3,
            enum_Shutting_Down = 4,
            enum_Not_Applicable = 5,
            enum_Enabled_but_Offline = 6,
            enum_In_Test = 7,
            enum_Deferred = 8,
            enum_Quiesce = 9,
            enum_Starting = 10,
            enum_DMTF_Reserved = 11,
            enum_Vendor_Reserved = 32768,
        };
        uint16 value;
        uint8 null;
    }
    EnabledState;
    Property<String> OtherEnabledState;
    struct _RequestedState
    {
        enum
        {
            enum_Enabled = 2,
            enum_Disabled = 3,
            enum_Shut_Down = 4,
            enum_No_Change = 5,
            enum_Offline = 6,
            enum_Test = 7,
            enum_Deferred = 8,
            enum_Quiesce = 9,
            enum_Reboot = 10,
            enum_Reset = 11,
            enum_Not_Applicable = 12,
            enum_DMTF_Reserved = 0,
            enum_Vendor_Reserved = 32768,
        };
        uint16 value;
        uint8 null;
    }
    RequestedState;
    struct _EnabledDefault
    {
        enum
        {
            enum_Enabled = 2,
            enum_Disabled = 3,
            enum_Not_Applicable = 5,
            enum_Enabled_but_Offline = 6,
            enum_No_Default = 7,
            enum_Quiesce = 9,
            enum_DMTF_Reserved = 0,
            enum_Vendor_Reserved = 32768,
        };
        uint16 value;
        uint8 null;
    }
    EnabledDefault;
    Property<Datetime> TimeOfLastStateChange;

    CIMPLE_CLASS(CIM_EnabledLogicalElement)
};

class CIM_EnabledLogicalElement_RequestStateChange_method : public Instance
{
public:
    Property<uint16> RequestedState;
    CIM_ConcreteJob* Job;
    Property<Datetime> TimeoutPeriod;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_EnabledLogicalElement_RequestStateChange_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_EnabledLogicalElement_h */
