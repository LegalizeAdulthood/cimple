//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "AAA.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Reference
_AAA_left;

const Meta_Reference
_AAA_left =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    &CCC::static_meta_class,
    CIMPLE_OFF(AAA,left)
};

extern const Meta_Reference
_AAA_right;

const Meta_Reference
_AAA_right =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "right",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    &DDD::static_meta_class,
    CIMPLE_OFF(AAA,right)
};

static const Meta_Reference
_AAA_fool_c =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "c",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    &CCC::static_meta_class,
    CIMPLE_OFF(AAA_fool_method,c)
};

static const Meta_Property
_AAA_fool_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(AAA_fool_method,return_value),
    0, /* value */
};

static Meta_Feature* _AAA_fool_MFA[] =
{
    (Meta_Feature*)&_AAA_fool_c,
    (Meta_Feature*)&_AAA_fool_return_value
};

const Meta_Method
AAA_fool_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "fool",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _AAA_fool_MFA,
    CIMPLE_ARRAY_SIZE(_AAA_fool_MFA),
    sizeof(AAA_fool_method),
    UINT32,
};

static Meta_Feature* _AAA_MFA[] =
{
    (Meta_Feature*)&_AAA_left,
    (Meta_Feature*)&_AAA_right,
    (Meta_Feature*)&AAA_fool_method::static_meta_class,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
};

const Meta_Class AAA::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "AAA",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _AAA_MFA,
    CIMPLE_ARRAY_SIZE(_AAA_MFA),
    sizeof(AAA),
    _locals,
    0, /* super_class */ 
    2, /* num_keys */
    0x40EE457B, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

