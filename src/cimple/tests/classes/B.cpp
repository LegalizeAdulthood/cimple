/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "B.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_A_w;

extern const Meta_Property
_B_x;

const Meta_Property
_B_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(B,x),
    0, /* value */
};

extern const Meta_Property
_B_y;

const Meta_Property
_B_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(B,y),
    0, /* value */
};

static Meta_Feature* _B_MFA[] =
{
    (Meta_Feature*)(void*)&_A_w,
    (Meta_Feature*)(void*)&_B_x,
    (Meta_Feature*)(void*)&_B_y,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
    {1},
};

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
    &A::static_meta_class,
    1, /* num_keys */
    0x39FB0704, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/classes/B.cpp,v 1.1 2007/04/17 19:45:42 mbrasher-public Exp $");
