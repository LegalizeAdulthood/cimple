/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Thing.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_28ABCBB935011A4E9C4EA34C17F23964;

extern const Meta_Property
_Thing_key;

const Meta_Property
_Thing_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Thing,key),
    0, /* value */
};

static Meta_Feature* _Thing_MFA[] =
{
    (Meta_Feature*)(void*)&_Thing_key,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class Thing::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Thing",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Thing_MFA,
    CIMPLE_ARRAY_SIZE(_Thing_MFA),
    sizeof(Thing),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_28ABCBB935011A4E9C4EA34C17F23964,
};

CIMPLE_NAMESPACE_END

