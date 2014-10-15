/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Methods.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_D96F5702319A18D7A0528AAD7806AA3F;

extern const Meta_Property
_Methods_key;

const Meta_Property
_Methods_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Methods,key),
    0, /* value */
};

static const Meta_Property
_Methods_foo_arg1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo_method,arg1),
    0, /* value */
};

static const Meta_Property
_Methods_foo_arg2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Methods_foo_method,arg2),
    0, /* value */
};

static const Meta_Property
_Methods_foo_arg3 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arg3",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(Methods_foo_method,arg3),
    0, /* value */
};

static const Meta_Property
_Methods_foo_arg4 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "arg4",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo_method,arg4),
    0, /* value */
};

static const Meta_Property
_Methods_foo_arg5 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "arg5",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Methods_foo_method,arg5),
    0, /* value */
};

static const Meta_Property
_Methods_foo_arg6 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "arg6",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(Methods_foo_method,arg6),
    0, /* value */
};

static const Meta_Property
_Methods_foo_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Methods_foo_method,return_value),
    0, /* value */
};

static Meta_Feature* _Methods_foo_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_foo_arg1,
    (Meta_Feature*)(void*)&_Methods_foo_arg2,
    (Meta_Feature*)(void*)&_Methods_foo_arg3,
    (Meta_Feature*)(void*)&_Methods_foo_arg4,
    (Meta_Feature*)(void*)&_Methods_foo_arg5,
    (Meta_Feature*)(void*)&_Methods_foo_arg6,
    (Meta_Feature*)(void*)&_Methods_foo_return_value
};

const Meta_Method
Methods_foo_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_foo_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_foo_MFA),
    sizeof(Methods_foo_method),
    STRING,
};

static const Meta_Reference
_Methods_foo2_arg1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "arg1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Arg::static_meta_class,
    CIMPLE_OFF(Methods_foo2_method,arg1)
};

static const Meta_Reference
_Methods_foo2_arg2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_OUT,
    "arg2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Arg::static_meta_class,
    CIMPLE_OFF(Methods_foo2_method,arg2)
};

static const Meta_Property
_Methods_foo2_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Methods_foo2_method,return_value),
    0, /* value */
};

static Meta_Feature* _Methods_foo2_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_foo2_arg1,
    (Meta_Feature*)(void*)&_Methods_foo2_arg2,
    (Meta_Feature*)(void*)&_Methods_foo2_return_value
};

const Meta_Method
Methods_foo2_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_foo2_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_foo2_MFA),
    sizeof(Methods_foo2_method),
    STRING,
};

static const Meta_Property
_Methods_foo3_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Methods_foo3_method,return_value),
    0, /* value */
};

static Meta_Feature* _Methods_foo3_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_foo3_return_value
};

const Meta_Method
Methods_foo3_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD|CIMPLE_FLAG_STATIC,
    "foo3",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_foo3_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_foo3_MFA),
    sizeof(Methods_foo3_method),
    STRING,
};

static const Meta_Property
_Methods_foo4_arr1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "arr1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1,
    CIMPLE_OFF(Methods_foo4_method,arr1),
    0, /* value */
};

static const Meta_Property
_Methods_foo4_arr2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "arr2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1,
    CIMPLE_OFF(Methods_foo4_method,arr2),
    0, /* value */
};

static const Meta_Property
_Methods_foo4_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo4_method,return_value),
    0, /* value */
};

static Meta_Feature* _Methods_foo4_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_foo4_arr1,
    (Meta_Feature*)(void*)&_Methods_foo4_arr2,
    (Meta_Feature*)(void*)&_Methods_foo4_return_value
};

const Meta_Method
Methods_foo4_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo4",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_foo4_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_foo4_MFA),
    sizeof(Methods_foo4_method),
    UINT32,
};

static const Meta_Property
_Methods_foo5_in_arg =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "in_arg",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo5_method,in_arg),
    0, /* value */
};

static const Meta_Property
_Methods_foo5_in_out_arg =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN|CIMPLE_FLAG_OUT,
    "in_out_arg",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo5_method,in_out_arg),
    0, /* value */
};

static const Meta_Property
_Methods_foo5_out_arg =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "out_arg",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo5_method,out_arg),
    0, /* value */
};

static const Meta_Property
_Methods_foo5_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_foo5_method,return_value),
    0, /* value */
};

static Meta_Feature* _Methods_foo5_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_foo5_in_arg,
    (Meta_Feature*)(void*)&_Methods_foo5_in_out_arg,
    (Meta_Feature*)(void*)&_Methods_foo5_out_arg,
    (Meta_Feature*)(void*)&_Methods_foo5_return_value
};

const Meta_Method
Methods_foo5_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo5",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_foo5_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_foo5_MFA),
    sizeof(Methods_foo5_method),
    UINT32,
};

static const Meta_Property
_Methods_junk_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_junk_method,x),
    0, /* value */
};

static const Meta_Property
_Methods_junk_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_junk_method,y),
    0, /* value */
};

static const Meta_Property
_Methods_junk_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Methods_junk_method,return_value),
    0, /* value */
};

static Meta_Feature* _Methods_junk_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_junk_x,
    (Meta_Feature*)(void*)&_Methods_junk_y,
    (Meta_Feature*)(void*)&_Methods_junk_return_value
};

const Meta_Method
Methods_junk_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "junk",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_junk_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_junk_MFA),
    sizeof(Methods_junk_method),
    UINT32,
};

static Meta_Feature* _Methods_MFA[] =
{
    (Meta_Feature*)(void*)&_Methods_key,
    (Meta_Feature*)(void*)&Methods_foo_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo2_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo3_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo4_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_foo5_method::static_meta_class,
    (Meta_Feature*)(void*)&Methods_junk_method::static_meta_class,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class Methods::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Methods",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Methods_MFA,
    CIMPLE_ARRAY_SIZE(_Methods_MFA),
    sizeof(Methods),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_D96F5702319A18D7A0528AAD7806AA3F,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test10/Methods.cpp,v 1.1 2007/06/19 15:27:23 mbrasher-public Exp $");
