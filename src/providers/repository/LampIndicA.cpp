/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "LampIndicA.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_21EDCD70A42E172A9DC460386EA6D93B;

extern const Meta_Property
_CIM_Indication_IndicationIdentifier;

extern const Meta_Property
_CIM_Indication_CorrelatedIndications;

extern const Meta_Property
_CIM_Indication_IndicationTime;

extern const Meta_Property
_CIM_Indication_PerceivedSeverity;

extern const Meta_Property
_CIM_Indication_OtherSeverity;

extern const Meta_Property
_LampIndic_message;

extern const Meta_Property
_LampIndicA_messageA;

const Meta_Property
_LampIndicA_messageA =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "messageA",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(LampIndicA,messageA),
    0, /* value */
};

static Meta_Feature* _LampIndicA_MFA[] =
{
    (Meta_Feature*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)&_LampIndic_message,
    (Meta_Feature*)&LampIndic_DeliverIndications_method::static_meta_class,
    (Meta_Feature*)&_LampIndicA_messageA,
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
    {1},
};

const Meta_Class LampIndicA::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_INDICATION,
    "LampIndicA",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _LampIndicA_MFA,
    CIMPLE_ARRAY_SIZE(_LampIndicA_MFA),
    sizeof(LampIndicA),
    _locals,
    &LampIndic::static_meta_class,
    0, /* num_keys */
    0x88D797ED, /* crc */
    &__meta_repository_21EDCD70A42E172A9DC460386EA6D93B,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/repository/LampIndicA.cpp,v 1.48 2007/03/13 22:53:18 mbrasher-public Exp $");
