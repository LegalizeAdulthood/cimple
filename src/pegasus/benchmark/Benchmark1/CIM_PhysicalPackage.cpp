//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_PhysicalPackage.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_5F56407F5BCA1C188DF80B644BFEBCD6;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_PhysicalElement_Description;

extern const Meta_Property
_CIM_PhysicalElement_ElementName;

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
_CIM_PhysicalElement_Tag;

extern const Meta_Property
_CIM_PhysicalElement_CreationClassName;

extern const Meta_Property
_CIM_PhysicalElement_Manufacturer;

extern const Meta_Property
_CIM_PhysicalElement_Model;

extern const Meta_Property
_CIM_PhysicalElement_SKU;

extern const Meta_Property
_CIM_PhysicalElement_SerialNumber;

extern const Meta_Property
_CIM_PhysicalElement_Version;

extern const Meta_Property
_CIM_PhysicalElement_PartNumber;

extern const Meta_Property
_CIM_PhysicalElement_OtherIdentifyingInfo;

extern const Meta_Property
_CIM_PhysicalElement_PoweredOn;

extern const Meta_Property
_CIM_PhysicalElement_ManufactureDate;

extern const Meta_Property
_CIM_PhysicalElement_VendorEquipmentType;

extern const Meta_Property
_CIM_PhysicalElement_UserTracking;

extern const Meta_Property
_CIM_PhysicalElement_CanBeFRUed;

extern const Meta_Property
_CIM_PhysicalPackage_RemovalConditions;

const Meta_Value_Scalar<uint16>
_CIM_PhysicalPackage_RemovalConditions_MV =
{
    2
};

const Meta_Property
_CIM_PhysicalPackage_RemovalConditions =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "RemovalConditions",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,RemovalConditions),
    (const Meta_Value*)&_CIM_PhysicalPackage_RemovalConditions_MV,
};

extern const Meta_Property
_CIM_PhysicalPackage_Removable;

const Meta_Property
_CIM_PhysicalPackage_Removable =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Removable",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,Removable),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalPackage_Replaceable;

const Meta_Property
_CIM_PhysicalPackage_Replaceable =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Replaceable",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,Replaceable),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalPackage_HotSwappable;

const Meta_Property
_CIM_PhysicalPackage_HotSwappable =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "HotSwappable",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,HotSwappable),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalPackage_Height;

const Meta_Property
_CIM_PhysicalPackage_Height =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Height",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,Height),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalPackage_Depth;

const Meta_Property
_CIM_PhysicalPackage_Depth =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Depth",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,Depth),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalPackage_Width;

const Meta_Property
_CIM_PhysicalPackage_Width =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Width",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,Width),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalPackage_Weight;

const Meta_Property
_CIM_PhysicalPackage_Weight =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Weight",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalPackage,Weight),
    0, /* value */
};

static const Meta_Reference
_CIM_PhysicalPackage_IsCompatible_ElementToCheck =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "ElementToCheck",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    &CIM_PhysicalElement::static_meta_class,
    CIMPLE_OFF(CIM_PhysicalPackage_IsCompatible_method,ElementToCheck)
};

static const Meta_Property
_CIM_PhysicalPackage_IsCompatible_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_PhysicalPackage_IsCompatible_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_PhysicalPackage_IsCompatible_MFA[] =
{
    (Meta_Feature*)&_CIM_PhysicalPackage_IsCompatible_ElementToCheck,
    (Meta_Feature*)&_CIM_PhysicalPackage_IsCompatible_return_value
};

const Meta_Method
CIM_PhysicalPackage_IsCompatible_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "IsCompatible",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_PhysicalPackage_IsCompatible_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_PhysicalPackage_IsCompatible_MFA),
    sizeof(CIM_PhysicalPackage_IsCompatible_method),
    UINT32,
};

static Meta_Feature* _CIM_PhysicalPackage_MFA[] =
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
    (Meta_Feature*)&_CIM_PhysicalPackage_RemovalConditions,
    (Meta_Feature*)&_CIM_PhysicalPackage_Removable,
    (Meta_Feature*)&_CIM_PhysicalPackage_Replaceable,
    (Meta_Feature*)&_CIM_PhysicalPackage_HotSwappable,
    (Meta_Feature*)&_CIM_PhysicalPackage_Height,
    (Meta_Feature*)&_CIM_PhysicalPackage_Depth,
    (Meta_Feature*)&_CIM_PhysicalPackage_Width,
    (Meta_Feature*)&_CIM_PhysicalPackage_Weight,
    (Meta_Feature*)&CIM_PhysicalPackage_IsCompatible_method::static_meta_class,
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
    {1},
    {1},
    {1},
};

const Meta_Class CIM_PhysicalPackage::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_PhysicalPackage",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_PhysicalPackage_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_PhysicalPackage_MFA),
    sizeof(CIM_PhysicalPackage),
    _locals,
    &CIM_PhysicalElement::static_meta_class,
    2, /* num_keys */
    0xFDD6B396, /* crc */
    &__meta_repository_5F56407F5BCA1C188DF80B644BFEBCD6,
};

CIMPLE_NAMESPACE_END

