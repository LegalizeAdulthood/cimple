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

extern const Meta_Repository __meta_repository_11737B1039C317579F5467253A6F1AFD;

extern const Meta_Reference _XYZ_LampLink_left;

const Meta_Reference _XYZ_LampLink_left =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    &XYZ_Lamp::static_meta_class,
    CIMPLE_OFF(XYZ_LampLink,left)
};

extern const Meta_Reference _XYZ_LampLink_right;

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

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class XYZ_LampLink::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "XYZ_LampLink",
    _XYZ_LampLink_meta_features,
    CIMPLE_ARRAY_SIZE(_XYZ_LampLink_meta_features),
    sizeof(XYZ_LampLink),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    2, /* num_keys */
    0xAC7E769B,/* crc */
    &__meta_repository_11737B1039C317579F5467253A6F1AFD,
};

CIMPLE_NAMESPACE_END

