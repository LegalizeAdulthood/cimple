//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Link2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_301C3D768E5D1704B1028C1944B9CD9D;

extern CIMPLE_HIDE const Meta_Reference _Link2_parent;

const Meta_Reference _Link2_parent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "parent",
    &Person2::static_meta_class,
    CIMPLE_OFF(Link2,parent)
};

extern CIMPLE_HIDE const Meta_Reference _Link2_child;

const Meta_Reference _Link2_child =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "child",
    &Person2::static_meta_class,
    CIMPLE_OFF(Link2,child)
};

static Meta_Feature* _Link2_meta_features[] =
{
    (Meta_Feature*)&_Link2_parent,
    (Meta_Feature*)&_Link2_child,
};

const Meta_Class Link2::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "Link2",
    _Link2_meta_features,
    CIMPLE_ARRAY_SIZE(_Link2_meta_features),
    sizeof(Link2),
    0,
    2,
    0xD4399ED2,
    &__meta_repository_301C3D768E5D1704B1028C1944B9CD9D,
};

CIMPLE_NAMESPACE_END

