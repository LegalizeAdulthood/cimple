/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Class4.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_FEA3A8EE2C1F13A39A7F0C91A76AFC64;

/*[1302]*/
extern const Meta_Property
_Class4_key;

/*[1325]*/
const Meta_Property
_Class4_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Class4,key),
    0, /* value */
};

extern const Meta_Reference
_Class4_embedded;

/*[1914]*/
const Meta_Reference _Class4_embedded =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_INSTANCE,
    "embedded",
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* subscript */
    &Class2::static_meta_class,
    CIMPLE_OFF(Class4,embedded)
};

/*[2025]*/
static Meta_Feature* _Class4_MFA[] =
{
    (Meta_Feature*)(void*)&_Class4_key,
    (Meta_Feature*)(void*)&_Class4_embedded,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

/*[2092]*/
const Meta_Class Class4::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Class4",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Class4_MFA,
    CIMPLE_ARRAY_SIZE(_Class4_MFA),
    sizeof(Class4),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_FEA3A8EE2C1F13A39A7F0C91A76AFC64,
};

CIMPLE_NAMESPACE_END

