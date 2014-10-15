//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_ManagedSystemElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_75E2CB8B53E2155E90DBB99ABED114CA;

extern const Meta_Property _CIM_ManagedElement_Caption;

extern const Meta_Property _CIM_ManagedElement_Description;

extern const Meta_Property _CIM_ManagedElement_ElementName;

extern const Meta_Property _CIM_ManagedSystemElement_InstallDate;

const Meta_Property _CIM_ManagedSystemElement_InstallDate =
{
    CIMPLE_FLAG_PROPERTY,
    "InstallDate",
    DATETIME,
    0,
    CIMPLE_OFF(CIM_ManagedSystemElement,InstallDate)
};

extern const Meta_Property _CIM_ManagedSystemElement_Name;

const Meta_Property _CIM_ManagedSystemElement_Name =
{
    CIMPLE_FLAG_PROPERTY,
    "Name",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedSystemElement,Name)
};

extern const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

const Meta_Property _CIM_ManagedSystemElement_OperationalStatus =
{
    CIMPLE_FLAG_PROPERTY,
    "OperationalStatus",
    UINT16,
    -1,
    CIMPLE_OFF(CIM_ManagedSystemElement,OperationalStatus)
};

extern const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions =
{
    CIMPLE_FLAG_PROPERTY,
    "StatusDescriptions",
    STRING,
    -1,
    CIMPLE_OFF(CIM_ManagedSystemElement,StatusDescriptions)
};

extern const Meta_Property _CIM_ManagedSystemElement_Status;

const Meta_Property _CIM_ManagedSystemElement_Status =
{
    CIMPLE_FLAG_PROPERTY,
    "Status",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedSystemElement,Status)
};

static Meta_Feature* _CIM_ManagedSystemElement_meta_features[] =
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

static const char* _super_classes[] =
{
    "CIM_ManagedElement",
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_ManagedSystemElement::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_ManagedSystemElement",
    _CIM_ManagedSystemElement_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_ManagedSystemElement_meta_features),
    sizeof(CIM_ManagedSystemElement),
    _locals,
    &CIM_ManagedElement::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0x5DB2A81C,/* crc */
    &__meta_repository_75E2CB8B53E2155E90DBB99ABED114CA,
};

CIMPLE_NAMESPACE_END

