//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "AAA2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

CIMPLE_HIDE
extern const Meta_Reference _AAA_left;

CIMPLE_HIDE
extern const Meta_Reference _AAA_right;

CIMPLE_HIDE
extern const Meta_Property _AAA2_aaa;

const Meta_Property _AAA2_aaa =
{
    CIMPLE_FLAG_PROPERTY,
    "aaa",
    UINT32,
    0,
    CIMPLE_OFF(AAA2,aaa)
};

static Meta_Feature* _AAA2_meta_features[] =
{
    (Meta_Feature*)&_AAA_left,
    (Meta_Feature*)&_AAA_right,
    (Meta_Feature*)&AAA_fool_method::static_meta_class,
    (Meta_Feature*)&_AAA2_aaa,
};

const Meta_Class AAA2::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "AAA2",
    _AAA2_meta_features,
    CIMPLE_ARRAY_SIZE(_AAA2_meta_features),
    sizeof(AAA2),
    &AAA::static_meta_class,
    2,
    0xA612DD62,
};

CIMPLE_NAMESPACE_END

