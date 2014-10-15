/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "BUG31_C.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_CE2FDEBA768A1A15997A464B13444CBC;

extern const Meta_Property
_BUG31_C_key;

const Meta_Property
_BUG31_C_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(BUG31_C,key),
    0, /* value */
};

static const Meta_Reference
_BUG31_C_meth_r =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "r",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &BUG31_A::static_meta_class,
    CIMPLE_OFF(BUG31_C_meth_method,r)
};

static const Meta_Reference
_BUG31_C_meth_s =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_OUT,
    "s",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &BUG31_A::static_meta_class,
    CIMPLE_OFF(BUG31_C_meth_method,s)
};

static const Meta_Property
_BUG31_C_meth_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(BUG31_C_meth_method,return_value),
    0, /* value */
};

static Meta_Feature* _BUG31_C_meth_MFA[] =
{
    (Meta_Feature*)(void*)&_BUG31_C_meth_r,
    (Meta_Feature*)(void*)&_BUG31_C_meth_s,
    (Meta_Feature*)(void*)&_BUG31_C_meth_return_value
};

const Meta_Method
BUG31_C_meth_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "meth",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _BUG31_C_meth_MFA,
    CIMPLE_ARRAY_SIZE(_BUG31_C_meth_MFA),
    sizeof(BUG31_C_meth_method),
    UINT32,
};

static Meta_Feature* _BUG31_C_MFA[] =
{
    (Meta_Feature*)(void*)&_BUG31_C_key,
    (Meta_Feature*)(void*)&BUG31_C_meth_method::static_meta_class,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class BUG31_C::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "BUG31_C",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _BUG31_C_MFA,
    CIMPLE_ARRAY_SIZE(_BUG31_C_MFA),
    sizeof(BUG31_C),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_CE2FDEBA768A1A15997A464B13444CBC,
};

CIMPLE_NAMESPACE_END

