/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "AY.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Reference
_AY_left;

const Meta_Reference
_AY_left =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE,
    "left",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Y::static_meta_class,
    CIMPLE_OFF(AY,left)
};

extern const Meta_Reference
_AY_right;

const Meta_Reference
_AY_right =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE,
    "right",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Y::static_meta_class,
    CIMPLE_OFF(AY,right)
};

static Meta_Feature* _AY_MFA[] =
{
    (Meta_Feature*)&_AY_left,
    (Meta_Feature*)&_AY_right,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class AY::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "AY",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _AY_MFA,
    CIMPLE_ARRAY_SIZE(_AY_MFA),
    sizeof(AY),
    _locals,
    &AX::static_meta_class,
    0, /* num_keys */
    0x57A8CE86, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/class/AY.cpp,v 1.16 2007/03/13 22:53:12 mbrasher-public Exp $");
