/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "ComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_538755081E31151DA78AAD14BC2E0477;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedElement_Caption;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedElement_Description;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedElement_ElementName;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

/*[1302]*/
extern const Meta_Property
_CIM_System_Name;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_OperationalStatus;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_StatusDescriptions;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_Status;

/*[1302]*/
extern const Meta_Property
_CIM_ManagedSystemElement_HealthState;

/*[1302]*/
extern const Meta_Property
_CIM_EnabledLogicalElement_EnabledState;

/*[1302]*/
extern const Meta_Property
_CIM_EnabledLogicalElement_OtherEnabledState;

/*[1302]*/
extern const Meta_Property
_CIM_EnabledLogicalElement_RequestedState;

/*[1302]*/
extern const Meta_Property
_CIM_EnabledLogicalElement_EnabledDefault;

/*[1302]*/
extern const Meta_Property
_CIM_EnabledLogicalElement_TimeOfLastStateChange;

/*[1302]*/
extern const Meta_Property
_CIM_System_CreationClassName;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_NameFormat;

/*[1302]*/
extern const Meta_Property
_CIM_System_PrimaryOwnerName;

/*[1302]*/
extern const Meta_Property
_CIM_System_PrimaryOwnerContact;

/*[1302]*/
extern const Meta_Property
_CIM_System_Roles;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_OtherIdentifyingInfo;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_IdentifyingDescriptions;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_Dedicated;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_OtherDedicatedDescriptions;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_ResetCapability;

/*[1302]*/
extern const Meta_Property
_CIM_ComputerSystem_PowerManagementCapabilities;

/*[2025]*/
static Meta_Feature* _ComputerSystem_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)(void*)&_CIM_System_Name,
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
    (Meta_Feature*)(void*)&_CIM_System_CreationClassName,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_NameFormat,
    (Meta_Feature*)(void*)&_CIM_System_PrimaryOwnerName,
    (Meta_Feature*)(void*)&_CIM_System_PrimaryOwnerContact,
    (Meta_Feature*)(void*)&_CIM_System_Roles,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_OtherIdentifyingInfo,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_IdentifyingDescriptions,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_Dedicated,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_OtherDedicatedDescriptions,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_ResetCapability,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_PowerManagementCapabilities,
    (Meta_Feature*)(void*)&CIM_ComputerSystem_SetPowerState_method::static_meta_class,
};

/*[2072]*/
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
};

/*[2092]*/
const Meta_Class ComputerSystem::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "ComputerSystem",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _ComputerSystem_MFA,
    CIMPLE_ARRAY_SIZE(_ComputerSystem_MFA),
    sizeof(ComputerSystem),
    _locals,
    &CIM_ComputerSystem::static_meta_class,
    2, /* num_keys */
    &__meta_repository_538755081E31151DA78AAD14BC2E0477,
};

CIMPLE_NAMESPACE_END

