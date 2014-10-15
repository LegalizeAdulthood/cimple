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

CIMPLE_HIDE
extern const Meta_Property _CIM_Indication_IndicationIdentifier;

CIMPLE_HIDE
extern const Meta_Property _CIM_Indication_CorrelatedIndications;

CIMPLE_HIDE
extern const Meta_Property _CIM_Indication_IndicationTime;

CIMPLE_HIDE
extern const Meta_Property _CIM_Indication_PerceivedSeverity;

CIMPLE_HIDE
extern const Meta_Property _CIM_Indication_OtherSeverity;

CIMPLE_HIDE
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

const Meta_Class DerivedIndication::static_meta_class =
{
    CIMPLE_FLAG_INDICATION,
    "DerivedIndication",
    _DerivedIndication_meta_features,
    CIMPLE_ARRAY_SIZE(_DerivedIndication_meta_features),
    sizeof(DerivedIndication),
    &MyIndication::static_meta_class,
    0,
    0x13422E13,
};

CIMPLE_NAMESPACE_END

