/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "B.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_821DC194D45D1F47A55FF349736C24E4;

/*[1302]*/
extern const Meta_Property
_B_key;

/*[1325]*/
const Meta_Property
_B_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(B,key),
    0, /* value */
};

/*[2025]*/
static Meta_Feature* _B_MFA[] =
{
    (Meta_Feature*)(void*)&_B_key,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
};

/*[2092]*/
const Meta_Class B::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "B",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _B_MFA,
    CIMPLE_ARRAY_SIZE(_B_MFA),
    sizeof(B),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_821DC194D45D1F47A55FF349736C24E4,
};

CIMPLE_NAMESPACE_END

