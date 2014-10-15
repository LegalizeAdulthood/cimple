//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_EnabledLogicalElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Caption;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Description;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_ElementName;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_Name;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedSystemElement_Status;

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledState;

const Meta_Property _CIM_EnabledLogicalElement_EnabledState =
{
    CIMPLE_FLAG_PROPERTY,
    "EnabledState",
    UINT16,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement,EnabledState)
};

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState;

const Meta_Property _CIM_EnabledLogicalElement_OtherEnabledState =
{
    CIMPLE_FLAG_PROPERTY,
    "OtherEnabledState",
    STRING,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement,OtherEnabledState)
};

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_RequestedState;

const Meta_Property _CIM_EnabledLogicalElement_RequestedState =
{
    CIMPLE_FLAG_PROPERTY,
    "RequestedState",
    UINT16,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement,RequestedState)
};

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault;

const Meta_Property _CIM_EnabledLogicalElement_EnabledDefault =
{
    CIMPLE_FLAG_PROPERTY,
    "EnabledDefault",
    UINT16,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement,EnabledDefault)
};

extern CIMPLE_HIDE const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange;

const Meta_Property _CIM_EnabledLogicalElement_TimeOfLastStateChange =
{
    CIMPLE_FLAG_PROPERTY,
    "TimeOfLastStateChange",
    DATETIME,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement,TimeOfLastStateChange)
};

static const Meta_Property _CIM_EnabledLogicalElement_RequestStateChange_RequestedState =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "RequestedState",
    UINT16,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,RequestedState)
};

static const Meta_Reference _CIM_EnabledLogicalElement_RequestStateChange_Job =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_OUT,
    "Job",
    &CIM_ConcreteJob::static_meta_class,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,Job)
};

static const Meta_Property _CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "TimeoutPeriod",
    DATETIME,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,TimeoutPeriod)
};

static const Meta_Property _CIM_EnabledLogicalElement_RequestStateChange_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(CIM_EnabledLogicalElement_RequestStateChange_method,return_value)
};

static Meta_Feature* _CIM_EnabledLogicalElement_RequestStateChange_meta_features[] =
{
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestStateChange_RequestedState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestStateChange_Job,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestStateChange_return_value
};

const Meta_Method CIM_EnabledLogicalElement_RequestStateChange_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "RequestStateChange",
    _CIM_EnabledLogicalElement_RequestStateChange_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_EnabledLogicalElement_RequestStateChange_meta_features),
    sizeof(CIM_EnabledLogicalElement_RequestStateChange_method),
    UINT32,
};

static Meta_Feature* _CIM_EnabledLogicalElement_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Name,
    (Meta_Feature*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_EnabledState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_OtherEnabledState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_RequestedState,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_EnabledDefault,
    (Meta_Feature*)&_CIM_EnabledLogicalElement_TimeOfLastStateChange,
    (Meta_Feature*)&CIM_EnabledLogicalElement_RequestStateChange_method::static_meta_class,
};

const Meta_Class CIM_EnabledLogicalElement::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_EnabledLogicalElement",
    _CIM_EnabledLogicalElement_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_EnabledLogicalElement_meta_features),
    sizeof(CIM_EnabledLogicalElement),
    &CIM_LogicalElement::static_meta_class,
    0,
    0xBDDFE92D,
};

CIMPLE_NAMESPACE_END

