//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "ThingLink.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_11737B1039C317579F5467253A6F1AFD;

extern const Meta_Reference _ThingLink_left;

const Meta_Reference _ThingLink_left =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    &Thing::static_meta_class,
    CIMPLE_OFF(ThingLink,left)
};

extern const Meta_Reference _ThingLink_right;

const Meta_Reference _ThingLink_right =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "right",
    &Thing::static_meta_class,
    CIMPLE_OFF(ThingLink,right)
};

static Meta_Feature* _ThingLink_meta_features[] =
{
    (Meta_Feature*)&_ThingLink_left,
    (Meta_Feature*)&_ThingLink_right,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class ThingLink::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "ThingLink",
    _ThingLink_meta_features,
    CIMPLE_ARRAY_SIZE(_ThingLink_meta_features),
    sizeof(ThingLink),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    2, /* num_keys */
    0x32F93684,/* crc */
    &__meta_repository_11737B1039C317579F5467253A6F1AFD,
};

CIMPLE_NAMESPACE_END

