//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_Card.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_75E2CB8B53E2155E90DBB99ABED114CA;

extern const Meta_Property _CIM_ManagedElement_Caption;

extern const Meta_Property _CIM_PhysicalElement_Description;

extern const Meta_Property _CIM_PhysicalElement_ElementName;

extern const Meta_Property _CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property _CIM_ManagedSystemElement_Name;

extern const Meta_Property _CIM_ManagedSystemElement_OperationalStatus;

extern const Meta_Property _CIM_ManagedSystemElement_StatusDescriptions;

extern const Meta_Property _CIM_ManagedSystemElement_Status;

extern const Meta_Property _CIM_PhysicalElement_Tag;

extern const Meta_Property _CIM_PhysicalElement_CreationClassName;

extern const Meta_Property _CIM_PhysicalElement_Manufacturer;

extern const Meta_Property _CIM_PhysicalElement_Model;

extern const Meta_Property _CIM_PhysicalElement_SKU;

extern const Meta_Property _CIM_PhysicalElement_SerialNumber;

extern const Meta_Property _CIM_PhysicalElement_Version;

extern const Meta_Property _CIM_PhysicalElement_PartNumber;

extern const Meta_Property _CIM_PhysicalElement_OtherIdentifyingInfo;

extern const Meta_Property _CIM_PhysicalElement_PoweredOn;

extern const Meta_Property _CIM_PhysicalElement_ManufactureDate;

extern const Meta_Property _CIM_PhysicalElement_VendorEquipmentType;

extern const Meta_Property _CIM_PhysicalElement_UserTracking;

extern const Meta_Property _CIM_PhysicalElement_CanBeFRUed;

extern const Meta_Property _CIM_PhysicalPackage_RemovalConditions;

extern const Meta_Property _CIM_PhysicalPackage_Removable;

extern const Meta_Property _CIM_PhysicalPackage_Replaceable;

extern const Meta_Property _CIM_PhysicalPackage_HotSwappable;

extern const Meta_Property _CIM_PhysicalPackage_Height;

extern const Meta_Property _CIM_PhysicalPackage_Depth;

extern const Meta_Property _CIM_PhysicalPackage_Width;

extern const Meta_Property _CIM_PhysicalPackage_Weight;

extern const Meta_Property _CIM_Card_HostingBoard;

const Meta_Property _CIM_Card_HostingBoard =
{
    CIMPLE_FLAG_PROPERTY,
    "HostingBoard",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_Card,HostingBoard)
};

extern const Meta_Property _CIM_Card_SlotLayout;

const Meta_Property _CIM_Card_SlotLayout =
{
    CIMPLE_FLAG_PROPERTY,
    "SlotLayout",
    STRING,
    0,
    CIMPLE_OFF(CIM_Card,SlotLayout)
};

extern const Meta_Property _CIM_Card_RequiresDaughterBoard;

const Meta_Property _CIM_Card_RequiresDaughterBoard =
{
    CIMPLE_FLAG_PROPERTY,
    "RequiresDaughterBoard",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_Card,RequiresDaughterBoard)
};

extern const Meta_Property _CIM_Card_SpecialRequirements;

const Meta_Property _CIM_Card_SpecialRequirements =
{
    CIMPLE_FLAG_PROPERTY,
    "SpecialRequirements",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_Card,SpecialRequirements)
};

extern const Meta_Property _CIM_Card_RequirementsDescription;

const Meta_Property _CIM_Card_RequirementsDescription =
{
    CIMPLE_FLAG_PROPERTY,
    "RequirementsDescription",
    STRING,
    0,
    CIMPLE_OFF(CIM_Card,RequirementsDescription)
};

extern const Meta_Property _CIM_Card_OperatingVoltages;

const Meta_Property _CIM_Card_OperatingVoltages =
{
    CIMPLE_FLAG_PROPERTY,
    "OperatingVoltages",
    SINT16,
    -1,
    CIMPLE_OFF(CIM_Card,OperatingVoltages)
};

static const Meta_Reference _CIM_Card_ConnectorPower_Connector =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "Connector",
    &CIM_PhysicalConnector::static_meta_class,
    CIMPLE_OFF(CIM_Card_ConnectorPower_method,Connector)
};

static const Meta_Property _CIM_Card_ConnectorPower_PoweredOn =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "PoweredOn",
    BOOLEAN,
    0,
    CIMPLE_OFF(CIM_Card_ConnectorPower_method,PoweredOn)
};

static const Meta_Property _CIM_Card_ConnectorPower_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(CIM_Card_ConnectorPower_method,return_value)
};

static Meta_Feature* _CIM_Card_ConnectorPower_meta_features[] =
{
    (Meta_Feature*)&_CIM_Card_ConnectorPower_Connector,
    (Meta_Feature*)&_CIM_Card_ConnectorPower_PoweredOn,
    (Meta_Feature*)&_CIM_Card_ConnectorPower_return_value
};

const Meta_Method CIM_Card_ConnectorPower_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "ConnectorPower",
    _CIM_Card_ConnectorPower_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_Card_ConnectorPower_meta_features),
    sizeof(CIM_Card_ConnectorPower_method),
    UINT32,
};

static Meta_Feature* _CIM_Card_meta_features[] =
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
    (Meta_Feature*)&_CIM_Card_HostingBoard,
    (Meta_Feature*)&_CIM_Card_SlotLayout,
    (Meta_Feature*)&_CIM_Card_RequiresDaughterBoard,
    (Meta_Feature*)&_CIM_Card_SpecialRequirements,
    (Meta_Feature*)&_CIM_Card_RequirementsDescription,
    (Meta_Feature*)&_CIM_Card_OperatingVoltages,
    (Meta_Feature*)&CIM_Card_ConnectorPower_method::static_meta_class,
};

static const char* _super_classes[] =
{
    "CIM_PhysicalPackage",
    "CIM_PhysicalElement",
    "CIM_ManagedSystemElement",
    "CIM_ManagedElement",
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
};

const Meta_Class CIM_Card::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_Card",
    _CIM_Card_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_Card_meta_features),
    sizeof(CIM_Card),
    _locals,
    &CIM_PhysicalPackage::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    2, /* num_keys */
    0x9C430412,/* crc */
    &__meta_repository_75E2CB8B53E2155E90DBB99ABED114CA,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Benchmark3/CIM_Card.cpp,v 1.3 2007/03/07 20:23:55 mbrasher-public Exp $");
