//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "AZ.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Reference _AZ_left;

const Meta_Reference _AZ_left =
{
    CIMPLE_FLAG_REFERENCE,
    "left",
    &Z::static_meta_class,
    CIMPLE_OFF(AZ,left)
};

extern const Meta_Reference _AY_right;

static Meta_Feature* _AZ_meta_features[] =
{
    (Meta_Feature*)&_AZ_left,
    (Meta_Feature*)&_AY_right,
};

static const char* _super_classes[] =
{
    "AY",
    "AX",
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {0},
};

const Meta_Class AZ::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "AZ",
    _AZ_meta_features,
    CIMPLE_ARRAY_SIZE(_AZ_meta_features),
    sizeof(AZ),
    _locals,
    &AY::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0x90FA576C,/* crc */
    0,
};

CIMPLE_NAMESPACE_END

