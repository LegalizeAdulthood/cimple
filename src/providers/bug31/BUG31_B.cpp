/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "BUG31_B.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_7039AE6F53A6105995C5669CB05A7C4F;

/*[1302]*/
extern const Meta_Property
_BUG31_A_prop1;

/*[1302]*/
extern const Meta_Property
_BUG31_B_key;

/*[1325]*/
const Meta_Property
_BUG31_B_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(BUG31_B,key),
    0, /* value */
};

/*[2025]*/
static Meta_Feature* _BUG31_B_MFA[] =
{
    (Meta_Feature*)(void*)&_BUG31_A_prop1,
    (Meta_Feature*)(void*)&_BUG31_B_key,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
};

/*[2092]*/
const Meta_Class BUG31_B::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "BUG31_B",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _BUG31_B_MFA,
    CIMPLE_ARRAY_SIZE(_BUG31_B_MFA),
    sizeof(BUG31_B),
    _locals,
    &BUG31_A::static_meta_class,
    1, /* num_keys */
    &__meta_repository_7039AE6F53A6105995C5669CB05A7C4F,
};

CIMPLE_NAMESPACE_END

