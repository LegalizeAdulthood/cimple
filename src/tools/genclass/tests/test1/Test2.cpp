/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Test2.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_Test2_ref_field1;

const Meta_Property
_Test2_ref_field1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ref_field1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(Test2,ref_field1),
    0, /* value */
};

extern const Meta_Property
_Test2_ref_field2;

const Meta_Property
_Test2_ref_field2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ref_field2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    SINT8,
    0, /* subscript */
    CIMPLE_OFF(Test2,ref_field2),
    0, /* value */
};

extern const Meta_Property
_Test2_ref_field3;

const Meta_Property
_Test2_ref_field3 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ref_field3",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Test2,ref_field3),
    0, /* value */
};

extern const Meta_Reference
_Test2_ref1;

const Meta_Reference
_Test2_ref1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE,
    "ref1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Test1::static_meta_class,
    CIMPLE_OFF(Test2,ref1)
};

extern const Meta_Reference
_Test2_ref2;

const Meta_Reference
_Test2_ref2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE,
    "ref2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Test1::static_meta_class,
    CIMPLE_OFF(Test2,ref2)
};

static Meta_Feature* _Test2_MFA[] =
{
    (Meta_Feature*)&_Test2_ref_field1,
    (Meta_Feature*)&_Test2_ref_field2,
    (Meta_Feature*)&_Test2_ref_field3,
    (Meta_Feature*)&_Test2_ref1,
    (Meta_Feature*)&_Test2_ref2,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class Test2::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "Test2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Test2_MFA,
    CIMPLE_ARRAY_SIZE(_Test2_MFA),
    sizeof(Test2),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    0xDC8273B9, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test1/Test2.cpp,v 1.22 2007/03/13 22:53:19 mbrasher-public Exp $");
