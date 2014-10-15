/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_ComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_0F481C54CB491EEFB353BBDA582D6D3E;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property
_CIM_System_Name;

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
_CIM_System_CreationClassName;

extern const Meta_Property
_CIM_ComputerSystem_NameFormat;

const Meta_Property
_CIM_ComputerSystem_NameFormat =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "NameFormat",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,NameFormat),
    0, /* value */
};

extern const Meta_Property
_CIM_System_PrimaryOwnerName;

extern const Meta_Property
_CIM_System_PrimaryOwnerContact;

extern const Meta_Property
_CIM_System_Roles;

extern const Meta_Property
_CIM_ComputerSystem_OtherIdentifyingInfo;

const Meta_Property
_CIM_ComputerSystem_OtherIdentifyingInfo =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherIdentifyingInfo",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,OtherIdentifyingInfo),
    0, /* value */
};

extern const Meta_Property
_CIM_ComputerSystem_IdentifyingDescriptions;

const Meta_Property
_CIM_ComputerSystem_IdentifyingDescriptions =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "IdentifyingDescriptions",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,IdentifyingDescriptions),
    0, /* value */
};

extern const Meta_Property
_CIM_ComputerSystem_Dedicated;

const Meta_Property
_CIM_ComputerSystem_Dedicated =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Dedicated",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,Dedicated),
    0, /* value */
};

extern const Meta_Property
_CIM_ComputerSystem_OtherDedicatedDescriptions;

const Meta_Property
_CIM_ComputerSystem_OtherDedicatedDescriptions =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherDedicatedDescriptions",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,OtherDedicatedDescriptions),
    0, /* value */
};

extern const Meta_Property
_CIM_ComputerSystem_ResetCapability;

const Meta_Property
_CIM_ComputerSystem_ResetCapability =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ResetCapability",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,ResetCapability),
    0, /* value */
};

extern const Meta_Property
_CIM_ComputerSystem_PowerManagementCapabilities;

const Meta_Property
_CIM_ComputerSystem_PowerManagementCapabilities =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "PowerManagementCapabilities",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_ComputerSystem,PowerManagementCapabilities),
    0, /* value */
};

static const Meta_Property
_CIM_ComputerSystem_SetPowerState_PowerState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "PowerState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_ComputerSystem_SetPowerState_method,PowerState),
    0, /* value */
};

static const Meta_Property
_CIM_ComputerSystem_SetPowerState_Time =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Time",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CIM_ComputerSystem_SetPowerState_method,Time),
    0, /* value */
};

static const Meta_Property
_CIM_ComputerSystem_SetPowerState_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_ComputerSystem_SetPowerState_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_ComputerSystem_SetPowerState_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_SetPowerState_PowerState,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_SetPowerState_Time,
    (Meta_Feature*)(void*)&_CIM_ComputerSystem_SetPowerState_return_value
};

const Meta_Method
CIM_ComputerSystem_SetPowerState_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "SetPowerState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_ComputerSystem_SetPowerState_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_ComputerSystem_SetPowerState_MFA),
    sizeof(CIM_ComputerSystem_SetPowerState_method),
    UINT32,
};

static Meta_Feature* _CIM_ComputerSystem_MFA[] =
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
    {1},
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
};

const Meta_Class CIM_ComputerSystem::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_ComputerSystem",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_ComputerSystem_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_ComputerSystem_MFA),
    sizeof(CIM_ComputerSystem),
    _locals,
    &CIM_System::static_meta_class,
    2, /* num_keys */
    &__meta_repository_0F481C54CB491EEFB353BBDA582D6D3E,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/ComputerSystemDiskDrive/CIM_ComputerSystem.cpp,v 1.8 2007/04/26 22:41:01 mbrasher-public Exp $");
