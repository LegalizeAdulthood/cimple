/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Right.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_D85A457900751F189001B5328CC747CD;

extern const Meta_Property
_Right_key;

const Meta_Property
_Right_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Right,key),
    0, /* value */
};

static Meta_Feature* _Right_MFA[] =
{
    (Meta_Feature*)(void*)&_Right_key,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class Right::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Right",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Right_MFA,
    CIMPLE_ARRAY_SIZE(_Right_MFA),
    sizeof(Right),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_D85A457900751F189001B5328CC747CD,
};

CIMPLE_NAMESPACE_END

