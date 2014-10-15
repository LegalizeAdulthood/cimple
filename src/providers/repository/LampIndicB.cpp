//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "LampIndicB.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_11737B1039C317579F5467253A6F1AFD;

extern const Meta_Property _CIM_Indication_IndicationIdentifier;

extern const Meta_Property _CIM_Indication_CorrelatedIndications;

extern const Meta_Property _CIM_Indication_IndicationTime;

extern const Meta_Property _CIM_Indication_PerceivedSeverity;

extern const Meta_Property _CIM_Indication_OtherSeverity;

extern const Meta_Property _LampIndic_message;

extern const Meta_Property _LampIndicB_messageB;

const Meta_Property _LampIndicB_messageB =
{
    CIMPLE_FLAG_PROPERTY,
    "messageB",
    STRING,
    0,
    CIMPLE_OFF(LampIndicB,messageB)
};

static Meta_Feature* _LampIndicB_meta_features[] =
{
    (Meta_Feature*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)&_LampIndic_message,
    (Meta_Feature*)&LampIndic_DeliverIndications_method::static_meta_class,
    (Meta_Feature*)&_LampIndicB_messageB,
};

static const char* _super_classes[] =
{
    "LampIndic",
    "CIM_Indication",
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

const Meta_Class LampIndicB::static_meta_class =
{
    CIMPLE_FLAG_INDICATION,
    "LampIndicB",
    _LampIndicB_meta_features,
    CIMPLE_ARRAY_SIZE(_LampIndicB_meta_features),
    sizeof(LampIndicB),
    _locals,
    &LampIndic::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0xC8E0BCBC,/* crc */
    &__meta_repository_11737B1039C317579F5467253A6F1AFD,
};

CIMPLE_NAMESPACE_END

