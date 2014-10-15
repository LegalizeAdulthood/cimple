/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_RedundancySet.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_8CCF8E58804E17C2BA75EC619FBC3236;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_SystemSpecificCollection_InstanceID;

extern const Meta_Property
_CIM_RedundancySet_RedundancyStatus;

const Meta_Property
_CIM_RedundancySet_RedundancyStatus =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "RedundancyStatus",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,RedundancyStatus),
    0, /* value */
};

extern const Meta_Property
_CIM_RedundancySet_TypeOfSet;

const Meta_Property
_CIM_RedundancySet_TypeOfSet =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TypeOfSet",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,TypeOfSet),
    0, /* value */
};

extern const Meta_Property
_CIM_RedundancySet_MinNumberNeeded;

const Meta_Property
_CIM_RedundancySet_MinNumberNeeded =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "MinNumberNeeded",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,MinNumberNeeded),
    0, /* value */
};

extern const Meta_Property
_CIM_RedundancySet_MaxNumberSupported;

const Meta_Property
_CIM_RedundancySet_MaxNumberSupported =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "MaxNumberSupported",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,MaxNumberSupported),
    0, /* value */
};

static const Meta_Reference
_CIM_RedundancySet_Failover_FailoverFrom =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "FailoverFrom",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_ManagedElement::static_meta_class,
    CIMPLE_OFF(CIM_RedundancySet_Failover_method,FailoverFrom)
};

static const Meta_Reference
_CIM_RedundancySet_Failover_FailoverTo =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "FailoverTo",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_ManagedElement::static_meta_class,
    CIMPLE_OFF(CIM_RedundancySet_Failover_method,FailoverTo)
};

static const Meta_Property
_CIM_RedundancySet_Failover_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_RedundancySet_Failover_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_RedundancySet_Failover_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_RedundancySet_Failover_FailoverFrom,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_Failover_FailoverTo,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_Failover_return_value
};

const Meta_Method
CIM_RedundancySet_Failover_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "Failover",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_RedundancySet_Failover_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_RedundancySet_Failover_MFA),
    sizeof(CIM_RedundancySet_Failover_method),
    UINT32,
};

extern const Meta_Property
_CIM_RedundancySet_VendorIdentifyingInfo;

const Meta_Property
_CIM_RedundancySet_VendorIdentifyingInfo =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "VendorIdentifyingInfo",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,VendorIdentifyingInfo),
    0, /* value */
};

extern const Meta_Property
_CIM_RedundancySet_OtherTypeOfSet;

const Meta_Property
_CIM_RedundancySet_OtherTypeOfSet =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherTypeOfSet",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,OtherTypeOfSet),
    0, /* value */
};

extern const Meta_Property
_CIM_RedundancySet_LoadBalanceAlgorithm;

static const Meta_Value_Scalar<uint16>
_CIM_RedundancySet_LoadBalanceAlgorithm_MV =
{
    2
};

const Meta_Property
_CIM_RedundancySet_LoadBalanceAlgorithm =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "LoadBalanceAlgorithm",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,LoadBalanceAlgorithm),
    (const Meta_Value*)(void*)&_CIM_RedundancySet_LoadBalanceAlgorithm_MV,
};

extern const Meta_Property
_CIM_RedundancySet_OtherLoadBalanceAlgorithm;

const Meta_Property
_CIM_RedundancySet_OtherLoadBalanceAlgorithm =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_WRITE,
    "OtherLoadBalanceAlgorithm",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_RedundancySet,OtherLoadBalanceAlgorithm),
    0, /* value */
};

static Meta_Feature* _CIM_RedundancySet_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_SystemSpecificCollection_InstanceID,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_RedundancyStatus,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_TypeOfSet,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_MinNumberNeeded,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_MaxNumberSupported,
    (Meta_Feature*)(void*)&CIM_RedundancySet_Failover_method::static_meta_class,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_VendorIdentifyingInfo,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_OtherTypeOfSet,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_LoadBalanceAlgorithm,
    (Meta_Feature*)(void*)&_CIM_RedundancySet_OtherLoadBalanceAlgorithm,
};

static const Meta_Feature_Local _locals[] =
{
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

const Meta_Class CIM_RedundancySet::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_RedundancySet",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_RedundancySet_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_RedundancySet_MFA),
    sizeof(CIM_RedundancySet),
    _locals,
    &CIM_SystemSpecificCollection::static_meta_class,
    1, /* num_keys */
    0xEF365BB4, /* crc */
    &__meta_repository_8CCF8E58804E17C2BA75EC619FBC3236,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/SNIA_SpareConfigurationService/CIM_RedundancySet.cpp,v 1.9 2007/04/18 03:29:40 mbrasher-public Exp $");
