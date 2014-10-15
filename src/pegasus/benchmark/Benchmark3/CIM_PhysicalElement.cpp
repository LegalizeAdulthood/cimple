//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_PhysicalElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_75E2CB8B53E2155E90DBB99ABED114CA;

extern const Meta_Property _CIM_ManagedElement_Caption;

extern const Meta_Property _CIM_PhysicalElement_Description;

const Meta_Property _CIM_PhysicalElement_Description =
{
    CIMPLE_FLAG_PROPERTY,
    "Description",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,Description)
};

extern const Meta_Property _CIM_PhysicalElement_ElementName;

const Meta_Property _CIM_PhysicalElement_ElementName =
{
    CIMPLE_FLAG_PROPERTY,
    "ElementName",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,ElementName)
};

extern const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property _CIM_ManagedSystemElement_Name;

extern const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern const Meta_Property _CIM_ManagedSystemElement_Status;

extern const Meta_Property _CIM_PhysicalElement_Tag;

const Meta_Property _CIM_PhysicalElement_Tag =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "Tag",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,Tag)
};

extern const Meta_Property _CIM_PhysicalElement_CreationClassName;

const Meta_Property _CIM_PhysicalElement_CreationClassName =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "CreationClassName",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,CreationClassName)
};

extern const Meta_Property _CIM_PhysicalElement_Manufacturer;

const Meta_Property _CIM_PhysicalElement_Manufacturer =
{
    CIMPLE_FLAG_PROPERTY,
    "Manufacturer",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,Manufacturer)
};

extern const Meta_Property _CIM_PhysicalElement_Model;

const Meta_Property _CIM_PhysicalElement_Model =
{
    CIMPLE_FLAG_PROPERTY,
    "Model",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,Model)
};

extern const Meta_Property _CIM_PhysicalElement_SKU;

const Meta_Property _CIM_PhysicalElement_SKU =
{
    CIMPLE_FLAG_PROPERTY,
    "SKU",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,SKU)
};

extern const Meta_Property _CIM_PhysicalElement_SerialNumber;

const Meta_Property _CIM_PhysicalElement_SerialNumber =
{
    CIMPLE_FLAG_PROPERTY,
    "SerialNumber",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,SerialNumber)
};

extern const Meta_Property _CIM_PhysicalElement_Version;

const Meta_Property _CIM_PhysicalElement_Version =
{
    CIMPLE_FLAG_PROPERTY,
    "Version",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,Version)
};

extern const Meta_Property _CIM_PhysicalElement_PartNumber;

const Meta_Property _CIM_PhysicalElement_PartNumber =
{
    CIMPLE_FLAG_PROPERTY,
    "PartNumber",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,PartNumber)
};

extern const Meta_Property _CIM_PhysicalElement_OtherIdentifyingInfo;

const Meta_Property _CIM_PhysicalElement_OtherIdentifyingInfo =
{
    CIMPLE_FLAG_PROPERTY,
    "OtherIdentifyingInfo",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,OtherIdentifyingInfo)
};

extern const Meta_Property _CIM_PhysicalElement_PoweredOn;

const Meta_Property _CIM_PhysicalElement_PoweredOn =
{
    CIMPLE_FLAG_PROPERTY,
    "PoweredOn",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,PoweredOn)
};

extern const Meta_Property _CIM_PhysicalElement_ManufactureDate;

const Meta_Property _CIM_PhysicalElement_ManufactureDate =
{
    CIMPLE_FLAG_PROPERTY,
    "ManufactureDate",
    DATETIME,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,ManufactureDate)
};

extern const Meta_Property _CIM_PhysicalElement_VendorEquipmentType;

const Meta_Property _CIM_PhysicalElement_VendorEquipmentType =
{
    CIMPLE_FLAG_PROPERTY,
    "VendorEquipmentType",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,VendorEquipmentType)
};

extern const Meta_Property _CIM_PhysicalElement_UserTracking;

const Meta_Property _CIM_PhysicalElement_UserTracking =
{
    CIMPLE_FLAG_PROPERTY,
    "UserTracking",
    STRING,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,UserTracking)
};

extern const Meta_Property _CIM_PhysicalElement_CanBeFRUed;

const Meta_Property _CIM_PhysicalElement_CanBeFRUed =
{
    CIMPLE_FLAG_PROPERTY,
    "CanBeFRUed",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_PhysicalElement,CanBeFRUed)
};

static Meta_Feature* _CIM_PhysicalElement_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_PhysicalElement_Description,
    (Meta_Feature*)&_CIM_PhysicalElement_ElementName,
    (Meta_Feature*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Name,
    (Meta_Feature*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)&_CIM_PhysicalElement_Tag,
    (Meta_Feature*)&_CIM_PhysicalElement_CreationClassName,
    (Meta_Feature*)&_CIM_PhysicalElement_Manufacturer,
    (Meta_Feature*)&_CIM_PhysicalElement_Model,
    (Meta_Feature*)&_CIM_PhysicalElement_SKU,
    (Meta_Feature*)&_CIM_PhysicalElement_SerialNumber,
    (Meta_Feature*)&_CIM_PhysicalElement_Version,
    (Meta_Feature*)&_CIM_PhysicalElement_PartNumber,
    (Meta_Feature*)&_CIM_PhysicalElement_OtherIdentifyingInfo,
    (Meta_Feature*)&_CIM_PhysicalElement_PoweredOn,
    (Meta_Feature*)&_CIM_PhysicalElement_ManufactureDate,
    (Meta_Feature*)&_CIM_PhysicalElement_VendorEquipmentType,
    (Meta_Feature*)&_CIM_PhysicalElement_UserTracking,
    (Meta_Feature*)&_CIM_PhysicalElement_CanBeFRUed,
};

static const char* _super_classes[] =
{
    "CIM_ManagedSystemElement",
    "CIM_ManagedElement",
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
    {1},
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
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_PhysicalElement::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_PhysicalElement",
    _CIM_PhysicalElement_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_PhysicalElement_meta_features),
    sizeof(CIM_PhysicalElement),
    _locals,
    &CIM_ManagedSystemElement::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    2, /* num_keys */
    0x071A04C4,/* crc */
    &__meta_repository_75E2CB8B53E2155E90DBB99ABED114CA,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Benchmark3/CIM_PhysicalElement.cpp,v 1.2 2007/03/07 20:23:55 mbrasher-public Exp $");
