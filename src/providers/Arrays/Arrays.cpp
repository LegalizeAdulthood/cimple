/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Arrays.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_C299679C7AC61129B413DED449191A6F;

extern const Meta_Property
_Arrays_key;

const Meta_Property
_Arrays_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Arrays,key),
    0, /* value */
};

extern const Meta_Property
_Arrays_arr;

const Meta_Property
_Arrays_arr =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "arr",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(Arrays,arr),
    0, /* value */
};

static Meta_Feature* _Arrays_MFA[] =
{
    (Meta_Feature*)(void*)&_Arrays_key,
    (Meta_Feature*)(void*)&_Arrays_arr,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class Arrays::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Arrays",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Arrays_MFA,
    CIMPLE_ARRAY_SIZE(_Arrays_MFA),
    sizeof(Arrays),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_C299679C7AC61129B413DED449191A6F,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Arrays/Arrays.cpp,v 1.7 2007/04/26 22:40:59 mbrasher-public Exp $");
