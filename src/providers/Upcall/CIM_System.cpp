/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_System.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_B244C90E05C710CB9BE4B0C96ACC8D85;

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

const Meta_Property
_CIM_System_Name =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "Name",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_System,Name),
    0, /* value */
};

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

const Meta_Property
_CIM_System_CreationClassName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "CreationClassName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_System,CreationClassName),
    0, /* value */
};

extern const Meta_Property
_CIM_System_NameFormat;

const Meta_Property
_CIM_System_NameFormat =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "NameFormat",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_System,NameFormat),
    0, /* value */
};

extern const Meta_Property
_CIM_System_PrimaryOwnerName;

const Meta_Property
_CIM_System_PrimaryOwnerName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "PrimaryOwnerName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_System,PrimaryOwnerName),
    0, /* value */
};

extern const Meta_Property
_CIM_System_PrimaryOwnerContact;

const Meta_Property
_CIM_System_PrimaryOwnerContact =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "PrimaryOwnerContact",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_System,PrimaryOwnerContact),
    0, /* value */
};

extern const Meta_Property
_CIM_System_Roles;

const Meta_Property
_CIM_System_Roles =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "Roles",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_System,Roles),
    0, /* value */
};

static Meta_Feature* _CIM_System_MFA[] =
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
    (Meta_Feature*)(void*)&_CIM_System_NameFormat,
    (Meta_Feature*)(void*)&_CIM_System_PrimaryOwnerName,
    (Meta_Feature*)(void*)&_CIM_System_PrimaryOwnerContact,
    (Meta_Feature*)(void*)&_CIM_System_Roles,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {0},
    {1},
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
};

const Meta_Class CIM_System::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_System",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_System_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_System_MFA),
    sizeof(CIM_System),
    _locals,
    &CIM_EnabledLogicalElement::static_meta_class,
    2, /* num_keys */
    &__meta_repository_B244C90E05C710CB9BE4B0C96ACC8D85,
};

CIMPLE_NAMESPACE_END

