/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_EnabledLogicalElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_0534992289351A029B38A12919E776DE;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property
_CIM_ManagedSystemElement_Name;

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

static const Meta_Value_Scalar<uint16>
_CIM_EnabledLogicalElement_EnabledState_MV =
{
    5
};

const Meta_Property
_CIM_EnabledLogicalElement_EnabledState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "EnabledState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_EnabledLogicalElement,EnabledState),
    (const Meta_Value*)(void*)&_CIM_EnabledLogicalElement_EnabledState_MV,
};

extern const Meta_Property
_CIM_EnabledLogicalElement_OtherEnabledState;

const Meta_Property
_CIM_EnabledLogicalElement_OtherEnabledState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherEnabledState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_EnabledLogicalElement,OtherEnabledState),
    0, /* value */
};

extern const Meta_Property
_CIM_EnabledLogicalElement_RequestedState;

static const Meta_Value_Scalar<uint16>
_CIM_EnabledLogicalElement_RequestedState_MV =
{
    12
};

const Meta_Property
_CIM_EnabledLogicalElement_RequestedState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "RequestedState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_EnabledLogicalElement,RequestedState),
    (const Meta_Value*)(void*)&_CIM_EnabledLogicalElement_RequestedState_MV,
};

extern const Meta_Property
_CIM_EnabledLogicalElement_EnabledDefault;

static const Meta_Value_Scalar<uint16>
_CIM_EnabledLogicalElement_EnabledDefault_MV =
{
    2
};

const Meta_Property
_CIM_EnabledLogicalElement_EnabledDefault =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "EnabledDefault",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_EnabledLogicalElement,EnabledDefault),
    (const Meta_Value*)(void*)&_CIM_EnabledLogicalElement_EnabledDefault_MV,
};

extern const Meta_Property
_CIM_EnabledLogicalElement_TimeOfLastStateChange;

const Meta_Property
_CIM_EnabledLogicalElement_TimeOfLastStateChange =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TimeOfLastStateChange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_EnabledLogicalElement,TimeOfLastStateChange),
    0, /* value */
};

static const Meta_Property
_CIM_EnabledLogicalElement_RequestStateChange_RequestedState =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "RequestedState",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,RequestedState),
    0, /* value */
};

static const Meta_Reference
_CIM_EnabledLogicalElement_RequestStateChange_Job =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_OUT,
    "Job",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_ConcreteJob::static_meta_class,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,Job)
};

static const Meta_Property
_CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "TimeoutPeriod",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,TimeoutPeriod),
    0, /* value */
};

static const Meta_Property
_CIM_EnabledLogicalElement_RequestStateChange_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_EnabledLogicalElement_RequestStateChange_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_RequestStateChange_RequestedState,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_RequestStateChange_Job,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod,
    (Meta_Feature*)(void*)&_CIM_EnabledLogicalElement_RequestStateChange_return_value
};

const Meta_Method
CIM_EnabledLogicalElement_RequestStateChange_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "RequestStateChange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_EnabledLogicalElement_RequestStateChange_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_EnabledLogicalElement_RequestStateChange_MFA),
    sizeof(CIM_EnabledLogicalElement_RequestStateChange_method),
    UINT32,
};

static Meta_Feature* _CIM_EnabledLogicalElement_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_Name,
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
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_EnabledLogicalElement::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_EnabledLogicalElement",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_EnabledLogicalElement_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_EnabledLogicalElement_MFA),
    sizeof(CIM_EnabledLogicalElement),
    _locals,
    &CIM_LogicalElement::static_meta_class,
    0, /* num_keys */
    &__meta_repository_0534992289351A029B38A12919E776DE,
};

CIMPLE_NAMESPACE_END

