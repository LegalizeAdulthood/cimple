//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_System.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Caption;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Description;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_ElementName;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern CIMPLE_HIDE const Meta_Property _CIM_System_Name;

const Meta_Property _CIM_System_Name =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "Name",
    STRING,
    0,
    CIMPLE_OFF(CIM_System,Name)
};

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_Status;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_RequestedState;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange;

extern CIMPLE_HIDE const Meta_Property _CIM_System_CreationClassName;

const Meta_Property _CIM_System_CreationClassName =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "CreationClassName",
    STRING,
    0,
    CIMPLE_OFF(CIM_System,CreationClassName)
};

extern CIMPLE_HIDE const Meta_Property _CIM_System_NameFormat;

const Meta_Property _CIM_System_NameFormat =
{
    CIMPLE_FLAG_PROPERTY,
    "NameFormat",
    STRING,
    0,
    CIMPLE_OFF(CIM_System,NameFormat)
};

extern CIMPLE_HIDE const Meta_Property _CIM_System_PrimaryOwnerName;

const Meta_Property _CIM_System_PrimaryOwnerName =
{
    CIMPLE_FLAG_PROPERTY,
    "PrimaryOwnerName",
    STRING,
    0,
    CIMPLE_OFF(CIM_System,PrimaryOwnerName)
};

extern CIMPLE_HIDE const Meta_Property _CIM_System_PrimaryOwnerContact;

const Meta_Property _CIM_System_PrimaryOwnerContact =
{
    CIMPLE_FLAG_PROPERTY,
    "PrimaryOwnerContact",
    STRING,
    0,
    CIMPLE_OFF(CIM_System,PrimaryOwnerContact)
};

extern CIMPLE_HIDE const Meta_Property _CIM_System_Roles;

const Meta_Property _CIM_System_Roles =
{
    CIMPLE_FLAG_PROPERTY,
    "Roles",
    STRING,
    -1,
    CIMPLE_OFF(CIM_System,Roles)
};

static Meta_Feature* _CIM_System_meta_features[] =
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
    (Meta_Feature*)&_CIM_System_NameFormat,
    (Meta_Feature*)&_CIM_System_PrimaryOwnerName,
    (Meta_Feature*)&_CIM_System_PrimaryOwnerContact,
    (Meta_Feature*)&_CIM_System_Roles,
};

const Meta_Class CIM_System::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_System",
    _CIM_System_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_System_meta_features),
    sizeof(CIM_System),
    &CIM_EnabledLogicalElement::static_meta_class,
    2,
    0x99E12464,
};

CIMPLE_NAMESPACE_END

