/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_StorageRedundancySet.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_1EFFCF5E346717DCBD81B2711E2620B8;

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

extern const Meta_Property
_CIM_RedundancySet_TypeOfSet;

extern const Meta_Property
_CIM_RedundancySet_MinNumberNeeded;

extern const Meta_Property
_CIM_RedundancySet_MaxNumberSupported;

extern const Meta_Property
_CIM_RedundancySet_VendorIdentifyingInfo;

extern const Meta_Property
_CIM_RedundancySet_OtherTypeOfSet;

extern const Meta_Property
_CIM_RedundancySet_LoadBalanceAlgorithm;

extern const Meta_Property
_CIM_RedundancySet_OtherLoadBalanceAlgorithm;

extern const Meta_Property
_CIM_StorageRedundancySet_TypeOfAlgorithm;

const Meta_Property
_CIM_StorageRedundancySet_TypeOfAlgorithm =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "TypeOfAlgorithm",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageRedundancySet,TypeOfAlgorithm),
    0, /* value */
};

extern const Meta_Property
_CIM_StorageRedundancySet_OtherAlgorithm;

const Meta_Property
_CIM_StorageRedundancySet_OtherAlgorithm =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherAlgorithm",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_StorageRedundancySet,OtherAlgorithm),
    0, /* value */
};

static Meta_Feature* _CIM_StorageRedundancySet_MFA[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_SystemSpecificCollection_InstanceID,
    (Meta_Feature*)&_CIM_RedundancySet_RedundancyStatus,
    (Meta_Feature*)&_CIM_RedundancySet_TypeOfSet,
    (Meta_Feature*)&_CIM_RedundancySet_MinNumberNeeded,
    (Meta_Feature*)&_CIM_RedundancySet_MaxNumberSupported,
    (Meta_Feature*)&CIM_RedundancySet_Failover_method::static_meta_class,
    (Meta_Feature*)&_CIM_RedundancySet_VendorIdentifyingInfo,
    (Meta_Feature*)&_CIM_RedundancySet_OtherTypeOfSet,
    (Meta_Feature*)&_CIM_RedundancySet_LoadBalanceAlgorithm,
    (Meta_Feature*)&_CIM_RedundancySet_OtherLoadBalanceAlgorithm,
    (Meta_Feature*)&_CIM_StorageRedundancySet_TypeOfAlgorithm,
    (Meta_Feature*)&_CIM_StorageRedundancySet_OtherAlgorithm,
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
    {1},
    {1},
};

const Meta_Class CIM_StorageRedundancySet::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_StorageRedundancySet",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_StorageRedundancySet_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_StorageRedundancySet_MFA),
    sizeof(CIM_StorageRedundancySet),
    _locals,
    &CIM_RedundancySet::static_meta_class,
    1, /* num_keys */
    0x01CA42E4, /* crc */
    &__meta_repository_1EFFCF5E346717DCBD81B2711E2620B8,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/SNIA_SpareConfigurationService/CIM_StorageRedundancySet.cpp,v 1.6 2007/03/08 15:17:23 mbrasher-public Exp $");
