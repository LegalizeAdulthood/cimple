/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "DerivedIndication.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_59AB7750F9FF18899D6174C1EBEDB037;

/*[1302]*/
extern const Meta_Property
_CIM_Indication_IndicationIdentifier;

/*[1302]*/
extern const Meta_Property
_CIM_Indication_CorrelatedIndications;

/*[1302]*/
extern const Meta_Property
_CIM_Indication_IndicationTime;

/*[1302]*/
extern const Meta_Property
_CIM_Indication_PerceivedSeverity;

/*[1302]*/
extern const Meta_Property
_CIM_Indication_OtherSeverity;

extern const Meta_Reference
_MyIndication_object;

/*[2025]*/
static Meta_Feature* _DerivedIndication_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_Indication_IndicationIdentifier,
    (Meta_Feature*)(void*)&_CIM_Indication_CorrelatedIndications,
    (Meta_Feature*)(void*)&_CIM_Indication_IndicationTime,
    (Meta_Feature*)(void*)&_CIM_Indication_PerceivedSeverity,
    (Meta_Feature*)(void*)&_CIM_Indication_OtherSeverity,
    (Meta_Feature*)(void*)&_MyIndication_object,
    (Meta_Feature*)(void*)&MyIndication_DeliverIndications_method::static_meta_class,
};

/*[2072]*/
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

/*[2092]*/
const Meta_Class DerivedIndication::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_INDICATION,
    "DerivedIndication",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _DerivedIndication_MFA,
    CIMPLE_ARRAY_SIZE(_DerivedIndication_MFA),
    sizeof(DerivedIndication),
    _locals,
    &MyIndication::static_meta_class,
    0, /* num_keys */
    &__meta_repository_59AB7750F9FF18899D6174C1EBEDB037,
};

CIMPLE_NAMESPACE_END

