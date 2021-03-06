//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_PhysicalConnector.h"

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
_CIM_PhysicalConnector_ConnectorPinout;

const Meta_Property
_CIM_PhysicalConnector_ConnectorPinout =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConnectorPinout",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,ConnectorPinout),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_ConnectorType;

const Meta_Property
_CIM_PhysicalConnector_ConnectorType =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConnectorType",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,ConnectorType),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_OtherTypeDescription;

const Meta_Property
_CIM_PhysicalConnector_OtherTypeDescription =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherTypeDescription",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,OtherTypeDescription),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_ConnectorGender;

const Meta_Property
_CIM_PhysicalConnector_ConnectorGender =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConnectorGender",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,ConnectorGender),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_ConnectorElectricalCharacteristics;

const Meta_Property
_CIM_PhysicalConnector_ConnectorElectricalCharacteristics =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConnectorElectricalCharacteristics",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,ConnectorElectricalCharacteristics),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_OtherElectricalCharacteristics;

const Meta_Property
_CIM_PhysicalConnector_OtherElectricalCharacteristics =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherElectricalCharacteristics",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,OtherElectricalCharacteristics),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_NumPhysicalPins;

const Meta_Property
_CIM_PhysicalConnector_NumPhysicalPins =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "NumPhysicalPins",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,NumPhysicalPins),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_ConnectorLayout;

const Meta_Property
_CIM_PhysicalConnector_ConnectorLayout =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConnectorLayout",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,ConnectorLayout),
    0, /* value */
};

extern const Meta_Property
_CIM_PhysicalConnector_ConnectorDescription;

const Meta_Property
_CIM_PhysicalConnector_ConnectorDescription =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ConnectorDescription",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_PhysicalConnector,ConnectorDescription),
    0, /* value */
};

static Meta_Feature* _CIM_PhysicalConnector_MFA[] =
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
    (Meta_Feature*)&_CIM_PhysicalConnector_ConnectorPinout,
    (Meta_Feature*)&_CIM_PhysicalConnector_ConnectorType,
    (Meta_Feature*)&_CIM_PhysicalConnector_OtherTypeDescription,
    (Meta_Feature*)&_CIM_PhysicalConnector_ConnectorGender,
    (Meta_Feature*)&_CIM_PhysicalConnector_ConnectorElectricalCharacteristics,
    (Meta_Feature*)&_CIM_PhysicalConnector_OtherElectricalCharacteristics,
    (Meta_Feature*)&_CIM_PhysicalConnector_NumPhysicalPins,
    (Meta_Feature*)&_CIM_PhysicalConnector_ConnectorLayout,
    (Meta_Feature*)&_CIM_PhysicalConnector_ConnectorDescription,
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

const Meta_Class CIM_PhysicalConnector::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_PhysicalConnector",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_PhysicalConnector_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_PhysicalConnector_MFA),
    sizeof(CIM_PhysicalConnector),
    _locals,
    &CIM_PhysicalElement::static_meta_class,
    2, /* num_keys */
    0xFF3314DE, /* crc */
    &__meta_repository_5F56407F5BCA1C188DF80B644BFEBCD6,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Benchmark1/CIM_PhysicalConnector.cpp,v 1.3 2007/03/07 20:22:58 mbrasher-public Exp $");
