//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Standalone.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_933548EDE4621629AEAC16B3AD1E0554;

extern const Meta_Property
_Standalone_key;

const Meta_Property
_Standalone_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Standalone,key),
    0, /* value */
};

static Meta_Feature* _Standalone_MFA[] =
{
    (Meta_Feature*)&_Standalone_key,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class Standalone::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Standalone",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Standalone_MFA,
    CIMPLE_ARRAY_SIZE(_Standalone_MFA),
    sizeof(Standalone),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    0xE7251808, /* crc */
    &__meta_repository_933548EDE4621629AEAC16B3AD1E0554,
};

CIMPLE_NAMESPACE_END

