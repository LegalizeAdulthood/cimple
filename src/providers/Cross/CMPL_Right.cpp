/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CMPL_Right.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_F4E528F227ED1CBD8BD1773E04D0F0A0;

extern const Meta_Property
_CMPL_Right_key;

const Meta_Property
_CMPL_Right_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(CMPL_Right,key),
    0, /* value */
};

static Meta_Feature* _CMPL_Right_MFA[] =
{
    (Meta_Feature*)&_CMPL_Right_key,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class CMPL_Right::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CMPL_Right",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CMPL_Right_MFA,
    CIMPLE_ARRAY_SIZE(_CMPL_Right_MFA),
    sizeof(CMPL_Right),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    0xAF546225, /* crc */
    &__meta_repository_F4E528F227ED1CBD8BD1773E04D0F0A0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/CMPL_Right.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
