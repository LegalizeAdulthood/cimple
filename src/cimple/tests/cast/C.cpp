/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "C.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_A_a;

extern const Meta_Property
_B_b;

extern const Meta_Property
_C_c;

const Meta_Property
_C_c =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "c",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(C,c),
    0, /* value */
};

static Meta_Feature* _C_MFA[] =
{
    (Meta_Feature*)(void*)&_A_a,
    (Meta_Feature*)(void*)&_B_b,
    (Meta_Feature*)(void*)&_C_c,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {1},
};

const Meta_Class C::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "C",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _C_MFA,
    CIMPLE_ARRAY_SIZE(_C_MFA),
    sizeof(C),
    _locals,
    &B::static_meta_class,
    0, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/cast/C.cpp,v 1.23 2007/04/26 22:40:57 mbrasher-public Exp $");
