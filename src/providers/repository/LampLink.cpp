//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "LampLink.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_B91863F7A56D16BB82F3EE00F1B6B434;

extern const Meta_Reference _LampLink_left;

const Meta_Reference _LampLink_left =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    &Lamp::static_meta_class,
    CIMPLE_OFF(LampLink,left)
};

extern const Meta_Reference _LampLink_right;

const Meta_Reference _LampLink_right =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "right",
    &Lamp::static_meta_class,
    CIMPLE_OFF(LampLink,right)
};

static Meta_Feature* _LampLink_meta_features[] =
{
    (Meta_Feature*)&_LampLink_left,
    (Meta_Feature*)&_LampLink_right,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class LampLink::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "LampLink",
    _LampLink_meta_features,
    CIMPLE_ARRAY_SIZE(_LampLink_meta_features),
    sizeof(LampLink),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    2, /* num_keys */
    0xF296277D,/* crc */
    &__meta_repository_B91863F7A56D16BB82F3EE00F1B6B434,
};

CIMPLE_NAMESPACE_END

