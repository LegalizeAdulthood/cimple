//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "C.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property _A_a;

extern const Meta_Property _B_b;

extern const Meta_Property _C_c;

const Meta_Property _C_c =
{
    CIMPLE_FLAG_PROPERTY,
    "c",
    UINT32,
    0,
    CIMPLE_OFF(C,c)
};

static Meta_Feature* _C_meta_features[] =
{
    (Meta_Feature*)&_A_a,
    (Meta_Feature*)&_B_b,
    (Meta_Feature*)&_C_c,
};

static const char* _super_classes[] =
{
    "B",
    "A",
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {1},
};

const Meta_Class C::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "C",
    _C_meta_features,
    CIMPLE_ARRAY_SIZE(_C_meta_features),
    sizeof(C),
    _locals,
    &B::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    0, /* num_keys */
    0xAFCF468A,/* crc */
    0,
};

CIMPLE_NAMESPACE_END

