/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "LampIndicC.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_671AC3807744173DA09223EAE9E4B34D;

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
_LampIndicC_messageC;

const Meta_Property
_LampIndicC_messageC =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "messageC",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(LampIndicC,messageC),
    0, /* value */
};

static Meta_Feature* _LampIndicC_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)(void*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)(void*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)(void*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)(void*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)(void*)&_LampIndic_message,
    (Meta_Feature*)(void*)&LampIndic_DeliverIndications_method::static_meta_class,
    (Meta_Feature*)(void*)&_LampIndicC_messageC,
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

const Meta_Class LampIndicC::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_INDICATION,
    "LampIndicC",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _LampIndicC_MFA,
    CIMPLE_ARRAY_SIZE(_LampIndicC_MFA),
    sizeof(LampIndicC),
    _locals,
    &LampIndic::static_meta_class,
    0, /* num_keys */
    &__meta_repository_671AC3807744173DA09223EAE9E4B34D,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Lamp/LampIndicC.cpp,v 1.8 2007/04/26 22:41:04 mbrasher-public Exp $");
