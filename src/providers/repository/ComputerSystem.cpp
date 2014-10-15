//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "ComputerSystem.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_301C3D768E5D1704B1028C1944B9CD9D;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Caption;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Description;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_ElementName;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern CIMPLE_HIDE const Meta_Property _CIM_System_Name;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_Status;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_RequestedState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange;

extern CIMPLE_HIDE const Meta_Property _CIM_System_CreationClassName;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_NameFormat;

extern CIMPLE_HIDE const Meta_Property _CIM_System_PrimaryOwnerName;

extern CIMPLE_HIDE const Meta_Property _CIM_System_PrimaryOwnerContact;

extern CIMPLE_HIDE const Meta_Property _CIM_System_Roles;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_OtherIdentifyingInfo;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_IdentifyingDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_Dedicated;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_OtherDedicatedDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_ResetCapability;

extern CIMPLE_HIDE const Meta_Property _CIM_ComputerSystem_PowerManagementCapabilities;

static Meta_Feature* _ComputerSystem_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)&_CIM_System_Name,
    (Meta_Feature*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_EnabledState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_OtherEnabledState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestedState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_EnabledDefault,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_TimeOfLastStateChange,
    (Meta_Feature*)&CIM_EnabledLogicalElement_RequestStateChange_method::static_meta_class,
    (Meta_Feature*)&_CIM_System_CreationClassName,
    (Meta_Feature*)&_CIM_ComputerSystem_NameFormat,
    (Meta_Feature*)&_CIM_System_PrimaryOwnerName,
    (Meta_Feature*)&_CIM_System_PrimaryOwnerContact,
    (Meta_Feature*)&_CIM_System_Roles,
    (Meta_Feature*)&_CIM_ComputerSystem_OtherIdentifyingInfo,
    (Meta_Feature*)&_CIM_ComputerSystem_IdentifyingDescriptions,
    (Meta_Feature*)&_CIM_ComputerSystem_Dedicated,
    (Meta_Feature*)&_CIM_ComputerSystem_OtherDedicatedDescriptions,
    (Meta_Feature*)&_CIM_ComputerSystem_ResetCapability,
    (Meta_Feature*)&_CIM_ComputerSystem_PowerManagementCapabilities,
    (Meta_Feature*)&CIM_ComputerSystem_SetPowerState_method::static_meta_class,
};

const Meta_Class ComputerSystem::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "ComputerSystem",
    _ComputerSystem_meta_features,
    CIMPLE_ARRAY_SIZE(_ComputerSystem_meta_features),
    sizeof(ComputerSystem),
    &CIM_ComputerSystem::static_meta_class,
    2,
    0x49DBC462,
    &__meta_repository_301C3D768E5D1704B1028C1944B9CD9D,
};

CIMPLE_NAMESPACE_END

