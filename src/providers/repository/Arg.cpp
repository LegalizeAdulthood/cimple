//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Arg.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_E277BAB546AC1F9B84FD3C4B6BE00B1C;

extern const Meta_Property _Arg_key;

const Meta_Property _Arg_key =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "key",
    UINT32,
    0,
    CIMPLE_OFF(Arg,key)
};

static Meta_Feature* _Arg_meta_features[] =
{
    (Meta_Feature*)&_Arg_key,
};

const Meta_Class Arg::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Arg",
    _Arg_meta_features,
    CIMPLE_ARRAY_SIZE(_Arg_meta_features),
    sizeof(Arg),
    0,
    1,
    0xB30E83B7,
    &__meta_repository_E277BAB546AC1F9B84FD3C4B6BE00B1C,
};

CIMPLE_NAMESPACE_END

