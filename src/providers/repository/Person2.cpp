//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Person2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_11737B1039C317579F5467253A6F1AFD;

extern const Meta_Property _Person2_ssn;

const Meta_Property _Person2_ssn =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "ssn",
    UINT32,
    0,
    CIMPLE_OFF(Person2,ssn)
};

extern const Meta_Property _Person2_first;

const Meta_Property _Person2_first =
{
    CIMPLE_FLAG_PROPERTY,
    "first",
    STRING,
    0,
    CIMPLE_OFF(Person2,first)
};

extern const Meta_Property _Person2_last;

const Meta_Property _Person2_last =
{
    CIMPLE_FLAG_PROPERTY,
    "last",
    STRING,
    0,
    CIMPLE_OFF(Person2,last)
};

static Meta_Feature* _Person2_meta_features[] =
{
    (Meta_Feature*)&_Person2_ssn,
    (Meta_Feature*)&_Person2_first,
    (Meta_Feature*)&_Person2_last,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
};

const Meta_Class Person2::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Person2",
    _Person2_meta_features,
    CIMPLE_ARRAY_SIZE(_Person2_meta_features),
    sizeof(Person2),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    1, /* num_keys */
    0xC232F9C9,/* crc */
    &__meta_repository_11737B1039C317579F5467253A6F1AFD,
};

CIMPLE_NAMESPACE_END

