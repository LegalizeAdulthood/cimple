//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Part.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_EA4D42DE96501C068A2E0C2F6B614B6E;

extern const Meta_Property _Part_key1;

const Meta_Property _Part_key1 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "key1",
    BOOLEAN,
    0,
    CIMPLE_OFF(Part,key1)
};

extern const Meta_Property _Part_key2;

const Meta_Property _Part_key2 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "key2",
    UINT64,
    0,
    CIMPLE_OFF(Part,key2)
};

extern const Meta_Property _Part_key3;

const Meta_Property _Part_key3 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "key3",
    STRING,
    0,
    CIMPLE_OFF(Part,key3)
};

extern const Meta_Property _Part_prop1;

const Meta_Property _Part_prop1 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop1",
    BOOLEAN,
    0,
    CIMPLE_OFF(Part,prop1)
};

extern const Meta_Property _Part_prop2;

const Meta_Property _Part_prop2 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop2",
    UINT64,
    0,
    CIMPLE_OFF(Part,prop2)
};

extern const Meta_Property _Part_prop3;

const Meta_Property _Part_prop3 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop3",
    STRING,
    0,
    CIMPLE_OFF(Part,prop3)
};

static Meta_Feature* _Part_meta_features[] =
{
    (Meta_Feature*)&_Part_key1,
    (Meta_Feature*)&_Part_key2,
    (Meta_Feature*)&_Part_key3,
    (Meta_Feature*)&_Part_prop1,
    (Meta_Feature*)&_Part_prop2,
    (Meta_Feature*)&_Part_prop3,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class Part::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Part",
    _Part_meta_features,
    CIMPLE_ARRAY_SIZE(_Part_meta_features),
    sizeof(Part),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    3, /* num_keys */
    0xDB3D3070,/* crc */
    &__meta_repository_EA4D42DE96501C068A2E0C2F6B614B6E,
};

CIMPLE_NAMESPACE_END

