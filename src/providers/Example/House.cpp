/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "House.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_C7BF6C6FB00317A9BC783810AA2DB41F;

/*[1302]*/
extern const Meta_Property
_House_key;

/*[1325]*/
const Meta_Property
_House_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(House,key),
    0, /* value */
};

/*[2025]*/
static Meta_Feature* _House_MFA[] =
{
    (Meta_Feature*)(void*)&_House_key,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
};

/*[2092]*/
const Meta_Class House::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "House",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _House_MFA,
    CIMPLE_ARRAY_SIZE(_House_MFA),
    sizeof(House),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_C7BF6C6FB00317A9BC783810AA2DB41F,
};

CIMPLE_NAMESPACE_END

