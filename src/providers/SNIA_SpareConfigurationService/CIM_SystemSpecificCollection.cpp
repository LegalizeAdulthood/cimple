/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_SystemSpecificCollection.h"

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

const Meta_Property
_CIM_SystemSpecificCollection_InstanceID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "InstanceID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_SystemSpecificCollection,InstanceID),
    0, /* value */
};

static Meta_Feature* _CIM_SystemSpecificCollection_MFA[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_SystemSpecificCollection_InstanceID,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {1},
};

const Meta_Class CIM_SystemSpecificCollection::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_SystemSpecificCollection",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_SystemSpecificCollection_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_SystemSpecificCollection_MFA),
    sizeof(CIM_SystemSpecificCollection),
    _locals,
    &CIM_Collection::static_meta_class,
    1, /* num_keys */
    0xCCAEDAA7, /* crc */
    &__meta_repository_1EFFCF5E346717DCBD81B2711E2620B8,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/SNIA_SpareConfigurationService/CIM_SystemSpecificCollection.cpp,v 1.6 2007/03/08 15:17:23 mbrasher-public Exp $");
