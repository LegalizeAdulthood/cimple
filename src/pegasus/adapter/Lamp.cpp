//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Lamp.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _Lamp_model;

const Meta_Property _Lamp_model =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "model",
    STRING,
    0,
    CIMPLE_OFF(Lamp,model)
};

extern CIMPLE_HIDE const Meta_Property _Lamp_vendor;

const Meta_Property _Lamp_vendor =
{
    CIMPLE_FLAG_PROPERTY,
    "vendor",
    STRING,
    0,
    CIMPLE_OFF(Lamp,vendor)
};

extern CIMPLE_HIDE const Meta_Property _Lamp_wattage;

const Meta_Property _Lamp_wattage =
{
    CIMPLE_FLAG_PROPERTY,
    "wattage",
    UINT32,
    0,
    CIMPLE_OFF(Lamp,wattage)
};

extern CIMPLE_HIDE const Meta_Property _Lamp_color;

const Meta_Property _Lamp_color =
{
    CIMPLE_FLAG_PROPERTY,
    "color",
    STRING,
    0,
    CIMPLE_OFF(Lamp,color)
};

static const Meta_Property _Lamp_foo_arg1 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg1",
    STRING,
    0,
    CIMPLE_OFF(Lamp_foo_method,arg1)
};

static const Meta_Property _Lamp_foo_arg2 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg2",
    STRING,
    0,
    CIMPLE_OFF(Lamp_foo_method,arg2)
};

static const Meta_Property _Lamp_foo_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(Lamp_foo_method,return_value)
};

static Meta_Feature* _Lamp_foo_meta_features[] =
{
    (Meta_Feature*)&_Lamp_foo_arg1,
    (Meta_Feature*)&_Lamp_foo_arg2,
    (Meta_Feature*)&_Lamp_foo_return_value
};

const Meta_Method Lamp_foo_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "foo",
    _Lamp_foo_meta_features,
    CIMPLE_ARRAY_SIZE(_Lamp_foo_meta_features),
    sizeof(Lamp_foo_method),
    UINT32,
};

static Meta_Feature* _Lamp_meta_features[] =
{
    (Meta_Feature*)&_Lamp_model,
    (Meta_Feature*)&_Lamp_vendor,
    (Meta_Feature*)&_Lamp_wattage,
    (Meta_Feature*)&_Lamp_color,
    (Meta_Feature*)&Lamp_foo_method::static_meta_class,
};

const Meta_Class Lamp::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Lamp",
    _Lamp_meta_features,
    CIMPLE_ARRAY_SIZE(_Lamp_meta_features),
    sizeof(Lamp),
    0,
    1,
    0x1AC5D1C7,
};

CIMPLE_NAMESPACE_END

