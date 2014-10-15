//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "XYZ_Lamp.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_48D39CF2E1A81164BA57916E443B1258;

extern const Meta_Property _XYZ_Lamp_model;

const Meta_Property _XYZ_Lamp_model =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "model",
    STRING,
    0,
    CIMPLE_OFF(XYZ_Lamp,model)
};

extern const Meta_Property _XYZ_Lamp_vendor;

const Meta_Property _XYZ_Lamp_vendor =
{
    CIMPLE_FLAG_PROPERTY,
    "vendor",
    STRING,
    0,
    CIMPLE_OFF(XYZ_Lamp,vendor)
};

extern const Meta_Property _XYZ_Lamp_wattage;

const Meta_Property _XYZ_Lamp_wattage =
{
    CIMPLE_FLAG_PROPERTY,
    "wattage",
    UINT32,
    0,
    CIMPLE_OFF(XYZ_Lamp,wattage)
};

extern const Meta_Property _XYZ_Lamp_color;

const Meta_Property _XYZ_Lamp_color =
{
    CIMPLE_FLAG_PROPERTY,
    "color",
    STRING,
    0,
    CIMPLE_OFF(XYZ_Lamp,color)
};

static const Meta_Property _XYZ_Lamp_foo_arg1 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg1",
    STRING,
    0,
    CIMPLE_OFF(XYZ_Lamp_foo_method,arg1)
};

static const Meta_Property _XYZ_Lamp_foo_arg2 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg2",
    STRING,
    0,
    CIMPLE_OFF(XYZ_Lamp_foo_method,arg2)
};

static const Meta_Property _XYZ_Lamp_foo_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(XYZ_Lamp_foo_method,return_value)
};

static Meta_Feature* _XYZ_Lamp_foo_meta_features[] =
{
    (Meta_Feature*)&_XYZ_Lamp_foo_arg1,
    (Meta_Feature*)&_XYZ_Lamp_foo_arg2,
    (Meta_Feature*)&_XYZ_Lamp_foo_return_value
};

const Meta_Method XYZ_Lamp_foo_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "foo",
    _XYZ_Lamp_foo_meta_features,
    CIMPLE_ARRAY_SIZE(_XYZ_Lamp_foo_meta_features),
    sizeof(XYZ_Lamp_foo_method),
    UINT32,
};

static Meta_Feature* _XYZ_Lamp_meta_features[] =
{
    (Meta_Feature*)&_XYZ_Lamp_model,
    (Meta_Feature*)&_XYZ_Lamp_vendor,
    (Meta_Feature*)&_XYZ_Lamp_wattage,
    (Meta_Feature*)&_XYZ_Lamp_color,
    (Meta_Feature*)&XYZ_Lamp_foo_method::static_meta_class,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class XYZ_Lamp::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "XYZ_Lamp",
    _XYZ_Lamp_meta_features,
    CIMPLE_ARRAY_SIZE(_XYZ_Lamp_meta_features),
    sizeof(XYZ_Lamp),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    1, /* num_keys */
    0x9076B604,/* crc */
    &__meta_repository_48D39CF2E1A81164BA57916E443B1258,
};

CIMPLE_NAMESPACE_END

