/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "B.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_A_a;

extern const Meta_Property
_B_b;

const Meta_Property
_B_b =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "b",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(B,b),
    0, /* value */
};

static Meta_Feature* _B_MFA[] =
{
    (Meta_Feature*)(void*)&_A_a,
    (Meta_Feature*)(void*)&_B_b,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
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
    0, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/cast/B.cpp,v 1.24 2007/06/19 15:24:54 mbrasher-public Exp $");
