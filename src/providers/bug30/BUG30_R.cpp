/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "BUG30_R.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_05344CB582411C00BD23C44473D6B600;

extern const Meta_Property
_BUG30_R_key;

const Meta_Property
_BUG30_R_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(BUG30_R,key),
    0, /* value */
};

static Meta_Feature* _BUG30_R_MFA[] =
{
    (Meta_Feature*)&_BUG30_R_key,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class BUG30_R::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "BUG30_R",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _BUG30_R_MFA,
    CIMPLE_ARRAY_SIZE(_BUG30_R_MFA),
    sizeof(BUG30_R),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    0x8D34E45A, /* crc */
    &__meta_repository_05344CB582411C00BD23C44473D6B600,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/bug30/BUG30_R.cpp,v 1.8 2007/03/13 22:53:14 mbrasher-public Exp $");
