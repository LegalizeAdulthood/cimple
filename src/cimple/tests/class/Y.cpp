//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Y.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

CIMPLE_HIDE
extern const Meta_Property _X_x;

CIMPLE_HIDE
extern const Meta_Property _Y_y;

const Meta_Property _Y_y =
{
    CIMPLE_FLAG_PROPERTY,
    "y",
    UINT32,
    0,
    CIMPLE_OFF(Y,y)
};

static Meta_Feature* _Y_meta_features[] =
{
    (Meta_Feature*)&_X_x,
    (Meta_Feature*)&_Y_y,
};

const Meta_Class Y::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Y",
    _Y_meta_features,
    CIMPLE_ARRAY_SIZE(_Y_meta_features),
    sizeof(Y),
    &X::static_meta_class,
    0,
    0x00D00792,
};

CIMPLE_NAMESPACE_END
