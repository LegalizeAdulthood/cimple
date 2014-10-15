/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_StoragePool.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_C2AA78B37C6515EB9DBF2BC150C67E7F;

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
_CIM_StoragePool_InstanceID;

const Meta_Property
_CIM_StoragePool_InstanceID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "InstanceID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_StoragePool,InstanceID),
    0, /* value */
};

extern const Meta_Property
_CIM_StoragePool_PoolID;

const Meta_Property
_CIM_StoragePool_PoolID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "PoolID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_StoragePool,PoolID),
    0, /* value */
};

extern const Meta_Property
_CIM_StoragePool_Primordial;

static const Meta_Value_Scalar<boolean>
_CIM_StoragePool_Primordial_MV =
{
    false
};

const Meta_Property
_CIM_StoragePool_Primordial =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Primordial",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(CIM_StoragePool,Primordial),
    (const Meta_Value*)(void*)&_CIM_StoragePool_Primordial_MV,
};

extern const Meta_Property
_CIM_StoragePool_TotalManagedSpace;

const Meta_Property
_CIM_StoragePool_TotalManagedSpace =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TotalManagedSpace",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_StoragePool,TotalManagedSpace),
    0, /* value */
};

extern const Meta_Property
_CIM_StoragePool_RemainingManagedSpace;

const Meta_Property
_CIM_StoragePool_RemainingManagedSpace =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "RemainingManagedSpace",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0, /* subscript */
    CIMPLE_OFF(CIM_StoragePool,RemainingManagedSpace),
    0, /* value */
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizes_ElementType =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "ElementType",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizes_method,ElementType),
    0, /* value */
};

static const Meta_Reference
_CIM_StoragePool_GetSupportedSizes_Goal =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "Goal",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_StorageSetting::static_meta_class,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizes_method,Goal)
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizes_Sizes =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "Sizes",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    -1,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizes_method,Sizes),
    0, /* value */
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizes_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizes_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_StoragePool_GetSupportedSizes_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizes_ElementType,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizes_Goal,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizes_Sizes,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizes_return_value
};

const Meta_Method
CIM_StoragePool_GetSupportedSizes_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "GetSupportedSizes",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_StoragePool_GetSupportedSizes_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_StoragePool_GetSupportedSizes_MFA),
    sizeof(CIM_StoragePool_GetSupportedSizes_method),
    UINT32,
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizeRange_ElementType =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "ElementType",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizeRange_method,ElementType),
    0, /* value */
};

static const Meta_Reference
_CIM_StoragePool_GetSupportedSizeRange_Goal =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "Goal",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_StorageSetting::static_meta_class,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizeRange_method,Goal)
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizeRange_MinimumVolumeSize =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "MinimumVolumeSize",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizeRange_method,MinimumVolumeSize),
    0, /* value */
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizeRange_MaximumVolumeSize =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "MaximumVolumeSize",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizeRange_method,MaximumVolumeSize),
    0, /* value */
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizeRange_VolumeSizeDivisor =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "VolumeSizeDivisor",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT64,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizeRange_method,VolumeSizeDivisor),
    0, /* value */
};

static const Meta_Property
_CIM_StoragePool_GetSupportedSizeRange_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetSupportedSizeRange_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_StoragePool_GetSupportedSizeRange_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizeRange_ElementType,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizeRange_Goal,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizeRange_MinimumVolumeSize,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizeRange_MaximumVolumeSize,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizeRange_VolumeSizeDivisor,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetSupportedSizeRange_return_value
};

const Meta_Method
CIM_StoragePool_GetSupportedSizeRange_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "GetSupportedSizeRange",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_StoragePool_GetSupportedSizeRange_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_StoragePool_GetSupportedSizeRange_MFA),
    sizeof(CIM_StoragePool_GetSupportedSizeRange_method),
    UINT32,
};

static const Meta_Reference
_CIM_StoragePool_GetAvailableExtents_Goal =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "Goal",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_StorageSetting::static_meta_class,
    CIMPLE_OFF(CIM_StoragePool_GetAvailableExtents_method,Goal)
};

static const Meta_Reference
_CIM_StoragePool_GetAvailableExtents_AvailableExtents =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN|CIMPLE_FLAG_OUT,
    "AvailableExtents",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    -1, /* subscript */
    &CIM_StorageExtent::static_meta_class,
    CIMPLE_OFF(CIM_StoragePool_GetAvailableExtents_method,AvailableExtents)
};

static const Meta_Property
_CIM_StoragePool_GetAvailableExtents_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CIM_StoragePool_GetAvailableExtents_method,return_value),
    0, /* value */
};

static Meta_Feature* _CIM_StoragePool_GetAvailableExtents_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetAvailableExtents_Goal,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetAvailableExtents_AvailableExtents,
    (Meta_Feature*)(void*)&_CIM_StoragePool_GetAvailableExtents_return_value
};

const Meta_Method
CIM_StoragePool_GetAvailableExtents_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "GetAvailableExtents",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_StoragePool_GetAvailableExtents_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_StoragePool_GetAvailableExtents_MFA),
    sizeof(CIM_StoragePool_GetAvailableExtents_method),
    UINT32,
};

static Meta_Feature* _CIM_StoragePool_MFA[] =
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
    (Meta_Feature*)(void*)&_CIM_StoragePool_InstanceID,
    (Meta_Feature*)(void*)&_CIM_StoragePool_PoolID,
    (Meta_Feature*)(void*)&_CIM_StoragePool_Primordial,
    (Meta_Feature*)(void*)&_CIM_StoragePool_TotalManagedSpace,
    (Meta_Feature*)(void*)&_CIM_StoragePool_RemainingManagedSpace,
    (Meta_Feature*)(void*)&CIM_StoragePool_GetSupportedSizes_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_StoragePool_GetSupportedSizeRange_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_StoragePool_GetAvailableExtents_method::static_meta_class,
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
    {1},
    {1},
};

const Meta_Class CIM_StoragePool::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_StoragePool",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_StoragePool_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_StoragePool_MFA),
    sizeof(CIM_StoragePool),
    _locals,
    &CIM_LogicalElement::static_meta_class,
    1, /* num_keys */
    0xCF82CDF5, /* crc */
    &__meta_repository_C2AA78B37C6515EB9DBF2BC150C67E7F,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MySpareConfigurationService/CIM_StoragePool.cpp,v 1.5 2007/04/18 03:29:39 mbrasher-public Exp $");
