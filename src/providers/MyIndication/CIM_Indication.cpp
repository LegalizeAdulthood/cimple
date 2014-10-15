/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_Indication.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_23E0204DAFA913B8B39F4644687C9072;

extern const Meta_Property
_CIM_Indication_IndicationIdentifier;

const Meta_Property
_CIM_Indication_IndicationIdentifier =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "IndicationIdentifier",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Indication,IndicationIdentifier),
    0, /* value */
};

extern const Meta_Property
_CIM_Indication_CorrelatedIndications;

const Meta_Property
_CIM_Indication_CorrelatedIndications =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "CorrelatedIndications",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_Indication,CorrelatedIndications),
    0, /* value */
};

extern const Meta_Property
_CIM_Indication_IndicationTime;

const Meta_Property
_CIM_Indication_IndicationTime =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "IndicationTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(CIM_Indication,IndicationTime),
    0, /* value */
};

extern const Meta_Property
_CIM_Indication_PerceivedSeverity;

const Meta_Property
_CIM_Indication_PerceivedSeverity =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "PerceivedSeverity",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_Indication,PerceivedSeverity),
    0, /* value */
};

extern const Meta_Property
_CIM_Indication_OtherSeverity;

const Meta_Property
_CIM_Indication_OtherSeverity =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherSeverity",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_Indication,OtherSeverity),
    0, /* value */
};

static Meta_Feature* _CIM_Indication_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)(void*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)(void*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)(void*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)(void*)&_CIM_Indication_OtherSeverity,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_Indication::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_INDICATION|CIMPLE_FLAG_ABSTRACT,
    "CIM_Indication",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_Indication_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_Indication_MFA),
    sizeof(CIM_Indication),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    &__meta_repository_23E0204DAFA913B8B39F4644687C9072,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MyIndication/CIM_Indication.cpp,v 1.12 2007/06/19 15:25:00 mbrasher-public Exp $");
