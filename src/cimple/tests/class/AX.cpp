//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "AX.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Reference _AX_left;

const Meta_Reference _AX_left =
{
    CIMPLE_FLAG_REFERENCE,
    "left",
    &X::static_meta_class,
    CIMPLE_OFF(AX,left)
};

extern const Meta_Reference _AX_right;

const Meta_Reference _AX_right =
{
    CIMPLE_FLAG_REFERENCE,
    "right",
    &X::static_meta_class,
    CIMPLE_OFF(AX,right)
};

static Meta_Feature* _AX_meta_features[] =
{
    (Meta_Feature*)&_AX_left,
    (Meta_Feature*)&_AX_right,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class AX::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "AX",
    _AX_meta_features,
    CIMPLE_ARRAY_SIZE(_AX_meta_features),
    sizeof(AX),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    0, /* num_keys */
    0xCAC665DC,/* crc */
    0,
};

CIMPLE_NAMESPACE_END

