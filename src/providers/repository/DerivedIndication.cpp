//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "DerivedIndication.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_B91863F7A56D16BB82F3EE00F1B6B434;

extern const Meta_Property _CIM_Indication_IndicationIdentifier;

extern const Meta_Property _CIM_Indication_CorrelatedIndications;

extern const Meta_Property _CIM_Indication_IndicationTime;

extern const Meta_Property _CIM_Indication_PerceivedSeverity;

extern const Meta_Property _CIM_Indication_OtherSeverity;

extern const Meta_Reference _MyIndication_object;

static Meta_Feature* _DerivedIndication_meta_features[] =
{
    (Meta_Feature*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)&_MyIndication_object,
    (Meta_Feature*)&MyIndication_DeliverIndications_method::static_meta_class,
};

static const char* _super_classes[] =
{
    "MyIndication",
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
};

const Meta_Class DerivedIndication::static_meta_class =
{
    CIMPLE_FLAG_INDICATION,
    "DerivedIndication",
    _DerivedIndication_meta_features,
    CIMPLE_ARRAY_SIZE(_DerivedIndication_meta_features),
    sizeof(DerivedIndication),
    _locals,
    &MyIndication::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0x13422E13,/* crc */
    &__meta_repository_B91863F7A56D16BB82F3EE00F1B6B434,
};

CIMPLE_NAMESPACE_END

