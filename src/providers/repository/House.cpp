//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "House.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_7E50A1B19DE218BAB02DA17EE255C350;

extern const Meta_Property _House_key;

const Meta_Property _House_key =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "key",
    STRING,
    0,
    CIMPLE_OFF(House,key)
};

static Meta_Feature* _House_meta_features[] =
{
    (Meta_Feature*)&_House_key,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class House::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "House",
    _House_meta_features,
    CIMPLE_ARRAY_SIZE(_House_meta_features),
    sizeof(House),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    1, /* num_keys */
    0x1E1F23CB,/* crc */
    &__meta_repository_7E50A1B19DE218BAB02DA17EE255C350,
};

CIMPLE_NAMESPACE_END

