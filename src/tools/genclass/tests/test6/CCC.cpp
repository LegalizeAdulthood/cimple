//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CCC.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _BBB_counter;

extern CIMPLE_HIDE const Meta_Property _CCC_key;

const Meta_Property _CCC_key =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "key",
    STRING,
    0,
    CIMPLE_OFF(CCC,key)
};

extern CIMPLE_HIDE const Meta_Property _CCC_bbb;

const Meta_Property _CCC_bbb =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "bbb",
    UINT32,
    0,
    CIMPLE_OFF(CCC,bbb)
};

static const Meta_Property _CCC_foo_arg1 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg1",
    STRING,
    0,
    CIMPLE_OFF(CCC_foo_method,arg1)
};

static const Meta_Property _CCC_foo_arg2 =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg2",
    STRING,
    0,
    CIMPLE_OFF(CCC_foo_method,arg2)
};

static const Meta_Property _CCC_foo_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(CCC_foo_method,return_value)
};

static Meta_Feature* _CCC_foo_meta_features[] =
{
    (Meta_Feature*)&_CCC_foo_arg1,
    (Meta_Feature*)&_CCC_foo_arg2,
    (Meta_Feature*)&_CCC_foo_return_value
};

const Meta_Method CCC_foo_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "foo",
    _CCC_foo_meta_features,
    CIMPLE_ARRAY_SIZE(_CCC_foo_meta_features),
    sizeof(CCC_foo_method),
    UINT32,
};

static Meta_Feature* _CCC_meta_features[] =
{
    (Meta_Feature*)&_BBB_counter,
    (Meta_Feature*)&_CCC_key,
    (Meta_Feature*)&_CCC_bbb,
    (Meta_Feature*)&CCC_foo_method::static_meta_class,
};

const Meta_Class CCC::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CCC",
    _CCC_meta_features,
    CIMPLE_ARRAY_SIZE(_CCC_meta_features),
    sizeof(CCC),
    &BBB::static_meta_class,
    2,
    0x3EA79480,
    0,
};

CIMPLE_NAMESPACE_END

