//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Y.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_X_x;

extern const Meta_Property
_Y_y;

const Meta_Property
_Y_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Y,y),
    0, /* value */
};

static Meta_Feature* _Y_MFA[] =
{
    (Meta_Feature*)&_X_x,
    (Meta_Feature*)&_Y_y,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
};

const Meta_Class Y::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Y_MFA,
    CIMPLE_ARRAY_SIZE(_Y_MFA),
    sizeof(Y),
    _locals,
    &X::static_meta_class,
    0, /* num_keys */
    0x00D00792, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

