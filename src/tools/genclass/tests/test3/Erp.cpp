/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Erp.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_Erp_w;

const Meta_Property
_Erp_w =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "w",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Erp,w),
    0, /* value */
};

extern const Meta_Property
_Erp_x;

const Meta_Property
_Erp_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Erp,x),
    0, /* value */
};

extern const Meta_Property
_Erp_y;

const Meta_Property
_Erp_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(Erp,y),
    0, /* value */
};

extern const Meta_Property
_Erp_z;

const Meta_Property
_Erp_z =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "z",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    3, /* subscript */
    CIMPLE_OFF(Erp,z),
    0, /* value */
};

static Meta_Feature* _Erp_MFA[] =
{
    (Meta_Feature*)&_Erp_w,
    (Meta_Feature*)&_Erp_x,
    (Meta_Feature*)&_Erp_y,
    (Meta_Feature*)&_Erp_z,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class Erp::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Erp",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Erp_MFA,
    CIMPLE_ARRAY_SIZE(_Erp_MFA),
    sizeof(Erp),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    0x308E8173, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test3/Erp.cpp,v 1.22 2007/03/13 22:53:20 mbrasher-public Exp $");
