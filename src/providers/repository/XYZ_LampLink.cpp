//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "XYZ_LampLink.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Reference _XYZ_LampLink_left;

const Meta_Reference _XYZ_LampLink_left =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    &XYZ_Lamp::static_meta_class,
    CIMPLE_OFF(XYZ_LampLink,left)
};

extern CIMPLE_HIDE const Meta_Reference _XYZ_LampLink_right;

const Meta_Reference _XYZ_LampLink_right =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "right",
    &XYZ_Lamp::static_meta_class,
    CIMPLE_OFF(XYZ_LampLink,right)
};

static Meta_Feature* _XYZ_LampLink_meta_features[] =
{
    (Meta_Feature*)&_XYZ_LampLink_left,
    (Meta_Feature*)&_XYZ_LampLink_right,
};

const Meta_Class XYZ_LampLink::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "XYZ_LampLink",
    _XYZ_LampLink_meta_features,
    CIMPLE_ARRAY_SIZE(_XYZ_LampLink_meta_features),
    sizeof(XYZ_LampLink),
    0,
    2,
    0xAC7E769B,
};

CIMPLE_NAMESPACE_END

