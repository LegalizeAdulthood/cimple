/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Sub2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_E4275E2C1A6C1DADAC2F7E477CBAF5C2;

extern const Meta_Property
_Super_key;

extern const Meta_Property
_Sub2_sub2;

const Meta_Property
_Sub2_sub2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "sub2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Sub2,sub2),
    0, /* value */
};

static Meta_Feature* _Sub2_MFA[] =
{
    (Meta_Feature*)&_Super_key,
    (Meta_Feature*)&_Sub2_sub2,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
};

const Meta_Class Sub2::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Sub2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Sub2_MFA,
    CIMPLE_ARRAY_SIZE(_Sub2_MFA),
    sizeof(Sub2),
    _locals,
    &Super::static_meta_class,
    1, /* num_keys */
    0xB38404CB, /* crc */
    &__meta_repository_E4275E2C1A6C1DADAC2F7E477CBAF5C2,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Super/Sub2.cpp,v 1.14 2007/03/13 22:53:13 mbrasher-public Exp $");
