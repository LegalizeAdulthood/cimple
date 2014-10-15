//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "XYZ_LampIndic.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_7E50A1B19DE218BAB02DA17EE255C350;

extern const Meta_Property _CIM_Indication_IndicationIdentifier;

extern const Meta_Property _CIM_Indication_CorrelatedIndications;

extern const Meta_Property _CIM_Indication_IndicationTime;

extern const Meta_Property _CIM_Indication_PerceivedSeverity;

extern const Meta_Property _CIM_Indication_OtherSeverity;

extern const Meta_Property _XYZ_LampIndic_message;

const Meta_Property _XYZ_LampIndic_message =
{
    CIMPLE_FLAG_PROPERTY,
    "message",
    STRING,
    0,
    CIMPLE_OFF(XYZ_LampIndic,message)
};

static const Meta_Property _XYZ_LampIndic_DeliverIndications_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(XYZ_LampIndic_DeliverIndications_method,return_value)
};

static Meta_Feature* _XYZ_LampIndic_DeliverIndications_meta_features[] =
{
    (Meta_Feature*)&_XYZ_LampIndic_DeliverIndications_return_value
};

const Meta_Method XYZ_LampIndic_DeliverIndications_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD|CIMPLE_FLAG_STATIC,
    "DeliverIndications",
    _XYZ_LampIndic_DeliverIndications_meta_features,
    CIMPLE_ARRAY_SIZE(_XYZ_LampIndic_DeliverIndications_meta_features),
    sizeof(XYZ_LampIndic_DeliverIndications_method),
    UINT32,
};

static Meta_Feature* _XYZ_LampIndic_meta_features[] =
{
    (Meta_Feature*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)&_XYZ_LampIndic_message,
    (Meta_Feature*)&XYZ_LampIndic_DeliverIndications_method::static_meta_class,
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

const Meta_Class XYZ_LampIndic::static_meta_class =
{
    CIMPLE_FLAG_INDICATION,
    "XYZ_LampIndic",
    _XYZ_LampIndic_meta_features,
    CIMPLE_ARRAY_SIZE(_XYZ_LampIndic_meta_features),
    sizeof(XYZ_LampIndic),
    _locals,
    &CIM_Indication::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0x890A2E07,/* crc */
    &__meta_repository_7E50A1B19DE218BAB02DA17EE255C350,
};

CIMPLE_NAMESPACE_END

