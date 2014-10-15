/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_ZZZ_ControllerSystem_h
#define _cimple_ZZZ_ControllerSystem_h

#include <cimple/cimple.h>
#include "CIM_ComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

class ZZZ_ControllerSystem : public Instance
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
    Property<uint16> HealthState;

    // CIM_LogicalElement features:

    // CIM_EnabledLogicalElement features:
    Property<uint16> EnabledState;
    Property<String> OtherEnabledState;
    Property<uint16> RequestedState;
    Property<uint16> EnabledDefault;
    Property<Datetime> TimeOfLastStateChange;

    // CIM_System features:
    Property<String> CreationClassName;
    Property<String> NameFormat;
    Property<String> PrimaryOwnerName;
    Property<String> PrimaryOwnerContact;
    Property<Array_String> Roles;

    // CIM_ComputerSystem features:
    Property<Array_String> OtherIdentifyingInfo;
    Property<Array_String> IdentifyingDescriptions;
    Property<Array_uint16> Dedicated;
    Property<Array_String> OtherDedicatedDescriptions;
    Property<uint16> ResetCapability;
    Property<Array_uint16> PowerManagementCapabilities;

    // ZZZ_ControllerSystem features:

    CIMPLE_CLASS(ZZZ_ControllerSystem)
};

typedef CIM_EnabledLogicalElement_RequestStateChange_method ZZZ_ControllerSystem_RequestStateChange_method;

typedef CIM_ComputerSystem_SetPowerState_method ZZZ_ControllerSystem_SetPowerState_method;

CIMPLE_NAMESPACE_END

#endif /* _cimple_ZZZ_ControllerSystem_h */
