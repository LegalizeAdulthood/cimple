/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Sub1.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_CBAFEB45BD26155C9E7D63A2914102EF;

/*[1302]*/
extern const Meta_Property
_Super_key;

/*[1302]*/
extern const Meta_Property
_Sub1_sub1;

/*[1325]*/
const Meta_Property
_Sub1_sub1 =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "sub1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Sub1,sub1),
    0, /* value */
};

/*[2025]*/
static Meta_Feature* _Sub1_MFA[] =
{
    (Meta_Feature*)(void*)&_Super_key,
    (Meta_Feature*)(void*)&_Sub1_sub1,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
};

/*[2092]*/
const Meta_Class Sub1::static_meta_class =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_CLASS,
    "Sub1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Sub1_MFA,
    CIMPLE_ARRAY_SIZE(_Sub1_MFA),
    sizeof(Sub1),
    _locals,
    &Super::static_meta_class,
    1, /* num_keys */
    &__meta_repository_CBAFEB45BD26155C9E7D63A2914102EF,
};

CIMPLE_NAMESPACE_END

