/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "E.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_E_e;

const Meta_Property
_E_e =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "e",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(E,e),
    0, /* value */
};

static Meta_Feature* _E_MFA[] =
{
    (Meta_Feature*)&_E_e,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class E::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "E",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _E_MFA,
    CIMPLE_ARRAY_SIZE(_E_MFA),
    sizeof(E),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    0x40B42E8F, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/cimple/tests/cast/E.cpp,v 1.18 2007/03/13 22:53:12 mbrasher-public Exp $");
