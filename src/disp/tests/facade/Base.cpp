//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Base.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property _Base_w;

const Meta_Property _Base_w =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_LOCAL,
    "w",
    BOOLEAN,
    0,
    CIMPLE_OFF(Base,w)
};

extern const Meta_Property _Base_x;

const Meta_Property _Base_x =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_LOCAL,
    "x",
    UINT32,
    0,
    CIMPLE_OFF(Base,x)
};

extern const Meta_Property _Base_y;

const Meta_Property _Base_y =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_LOCAL,
    "y",
    STRING,
    0,
    CIMPLE_OFF(Base,y)
};

extern const Meta_Property _Base_z;

const Meta_Property _Base_z =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_LOCAL,
    "z",
    UINT32,
    -1,
    CIMPLE_OFF(Base,z)
};

static Meta_Feature* _Base_meta_features[] =
{
    (Meta_Feature*)&_Base_w,
    (Meta_Feature*)&_Base_x,
    (Meta_Feature*)&_Base_y,
    (Meta_Feature*)&_Base_z,
};

const Meta_Class Base::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Base",
    _Base_meta_features,
    CIMPLE_ARRAY_SIZE(_Base_meta_features),
    sizeof(Base),
    0,
    0,
};

CIMPLE_NAMESPACE_END
