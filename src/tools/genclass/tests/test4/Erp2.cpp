//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Erp2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _Erp2_w;

const Meta_Property _Erp2_w =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "w",
    STRING,
    0,
    CIMPLE_OFF(Erp2,w)
};

extern CIMPLE_HIDE const Meta_Property _Erp2_x;

const Meta_Property _Erp2_x =
{
    CIMPLE_FLAG_PROPERTY,
    "x",
    UINT32,
    0,
    CIMPLE_OFF(Erp2,x)
};

extern CIMPLE_HIDE const Meta_Property _Erp2_y;

const Meta_Property _Erp2_y =
{
    CIMPLE_FLAG_PROPERTY,
    "y",
    STRING,
    -1,
    CIMPLE_OFF(Erp2,y)
};

extern CIMPLE_HIDE const Meta_Property _Erp2_z;

const Meta_Property _Erp2_z =
{
    CIMPLE_FLAG_PROPERTY,
    "z",
    STRING,
    3,
    CIMPLE_OFF(Erp2,z)
};

static Meta_Feature* _Erp2_meta_features[] =
{
    (Meta_Feature*)&_Erp2_w,
    (Meta_Feature*)&_Erp2_x,
    (Meta_Feature*)&_Erp2_y,
    (Meta_Feature*)&_Erp2_z,
};

const Meta_Class Erp2::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Erp2",
    _Erp2_meta_features,
    CIMPLE_ARRAY_SIZE(_Erp2_meta_features),
    sizeof(Erp2),
    0,
    1,
    0x2DA47FD5,
};

CIMPLE_NAMESPACE_END
