//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "LampIndic.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_48D39CF2E1A81164BA57916E443B1258;

extern const Meta_Property _CIM_Indication_IndicationIdentifier;

extern const Meta_Property _CIM_Indication_CorrelatedIndications;

extern const Meta_Property _CIM_Indication_IndicationTime;

extern const Meta_Property _CIM_Indication_PerceivedSeverity;

extern const Meta_Property _CIM_Indication_OtherSeverity;

extern const Meta_Property _LampIndic_message;

const Meta_Property _LampIndic_message =
{
    CIMPLE_FLAG_PROPERTY,
    "message",
    STRING,
    0,
    CIMPLE_OFF(LampIndic,message)
};

static const Meta_Property _LampIndic_DeliverIndications_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(LampIndic_DeliverIndications_method,return_value)
};

static Meta_Feature* _LampIndic_DeliverIndications_meta_features[] =
{
    (Meta_Feature*)&_LampIndic_DeliverIndications_return_value
};

const Meta_Method LampIndic_DeliverIndications_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD|CIMPLE_FLAG_STATIC,
    "DeliverIndications",
    _LampIndic_DeliverIndications_meta_features,
    CIMPLE_ARRAY_SIZE(_LampIndic_DeliverIndications_meta_features),
    sizeof(LampIndic_DeliverIndications_method),
    UINT32,
};

static Meta_Feature* _LampIndic_meta_features[] =
{
    (Meta_Feature*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)&_LampIndic_message,
    (Meta_Feature*)&LampIndic_DeliverIndications_method::static_meta_class,
};

static const char* _super_classes[] =
{
    "CIM_Indication",
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {0},
    {0},
    {1},
    {1},
};

const Meta_Class LampIndic::static_meta_class =
{
    CIMPLE_FLAG_INDICATION,
    "LampIndic",
    _LampIndic_meta_features,
    CIMPLE_ARRAY_SIZE(_LampIndic_meta_features),
    sizeof(LampIndic),
    _locals,
    &CIM_Indication::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0x55719B5E,/* crc */
    &__meta_repository_48D39CF2E1A81164BA57916E443B1258,
};

CIMPLE_NAMESPACE_END

