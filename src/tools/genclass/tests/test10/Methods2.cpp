/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Methods2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_6E895D185835107AAE5C131DFD3C3016;

/*[1302]*/
extern const Meta_Property
_Methods_key;

/*[1516]*/
static const Meta_Property
_Methods2_junk_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods2_junk_method,x),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_Methods2_junk_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods2_junk_method,y),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_Methods2_junk_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods2_junk_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Methods2_junk_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods2_junk_x,
    (Meta_Feature*)(void*)&_Methods2_junk_y,
    (Meta_Feature*)(void*)&_Methods2_junk_return_value
};

/*[1847]*/
const Meta_Method
Methods2_junk_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "junk",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods2_junk_MFA,
    CIMPLE_ARRAY_SIZE(_Methods2_junk_MFA),
    sizeof(Methods2_junk_method),
    UINT32,
};

/*[2025]*/
static Meta_Feature* _Methods2_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_key,
    (Meta_Feature*)(void*)&Methods_foo_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo2_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo3_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo4_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo5_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_junk_method::static_meta_class,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {1},
};

/*[2092]*/
const Meta_Class Methods2::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Methods2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods2_MFA,
    CIMPLE_ARRAY_SIZE(_Methods2_MFA),
    sizeof(Methods2),
    _locals,
    &Methods::static_meta_class,
    1, /* num_keys */
    &__meta_repository_6E895D185835107AAE5C131DFD3C3016,
};

CIMPLE_NAMESPACE_END

