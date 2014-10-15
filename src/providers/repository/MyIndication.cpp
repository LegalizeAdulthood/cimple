//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "MyIndication.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_B91863F7A56D16BB82F3EE00F1B6B434;

extern const Meta_Property _CIM_Indication_IndicationIdentifier;

extern const Meta_Property _CIM_Indication_CorrelatedIndications;

extern const Meta_Property _CIM_Indication_IndicationTime;

extern const Meta_Property _CIM_Indication_PerceivedSeverity;

extern const Meta_Property _CIM_Indication_OtherSeverity;

extern const Meta_Reference _MyIndication_object;

const Meta_Reference _MyIndication_object =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,
    "object",
    &Instance::static_meta_class,
    CIMPLE_OFF(MyIndication,object)
};

static const Meta_Property _MyIndication_DeliverIndications_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(MyIndication_DeliverIndications_method,return_value)
};

static Meta_Feature* _MyIndication_DeliverIndications_meta_features[] =
{
    (Meta_Feature*)&_MyIndication_DeliverIndications_return_value
};

const Meta_Method MyIndication_DeliverIndications_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD|CIMPLE_FLAG_STATIC,
    "DeliverIndications",
    _MyIndication_DeliverIndications_meta_features,
    CIMPLE_ARRAY_SIZE(_MyIndication_DeliverIndications_meta_features),
    sizeof(MyIndication_DeliverIndications_method),
    UINT32,
};

static Meta_Feature* _MyIndication_meta_features[] =
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

const Meta_Class MyIndication::static_meta_class =
{
    CIMPLE_FLAG_INDICATION,
    "MyIndication",
    _MyIndication_meta_features,
    CIMPLE_ARRAY_SIZE(_MyIndication_meta_features),
    sizeof(MyIndication),
    _locals,
    &CIM_Indication::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0x1777CCD1,/* crc */
    &__meta_repository_B91863F7A56D16BB82F3EE00F1B6B434,
};

CIMPLE_NAMESPACE_END

