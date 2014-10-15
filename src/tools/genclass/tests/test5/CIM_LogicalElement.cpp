//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_LogicalElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property _CIM_ManagedElement_Caption;

extern const Meta_Property _CIM_ManagedElement_Description;

extern const Meta_Property _CIM_ManagedElement_ElementName;

extern const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property _CIM_ManagedSystemElement_Name;

extern const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern const Meta_Property _CIM_ManagedSystemElement_Status;

static Meta_Feature* _CIM_LogicalElement_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Name,
    (Meta_Feature*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Status,
};

const Meta_Class CIM_LogicalElement::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_LogicalElement",
    _CIM_LogicalElement_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalElement_meta_features),
    sizeof(CIM_LogicalElement),
    &CIM_ManagedSystemElement::static_meta_class,
    0,
    0xE3ABB7C2,
    0,
};

CIMPLE_NAMESPACE_END

