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

extern const Meta_Property _Test2_ref_field1;

const Meta_Property _Test2_ref_field1 =
{
    CIMPLE_FLAG_PROPERTY,
    "ref_field1",
    BOOLEAN,
    0,
    CIMPLE_OFF(Test2,ref_field1)
};

extern const Meta_Property _Test2_ref_field2;

const Meta_Property _Test2_ref_field2 =
{
    CIMPLE_FLAG_PROPERTY,
    "ref_field2",
    SINT8,
    0,
    CIMPLE_OFF(Test2,ref_field2)
};

extern const Meta_Property _Test2_ref_field3;

const Meta_Property _Test2_ref_field3 =
{
    CIMPLE_FLAG_PROPERTY,
    "ref_field3",
    STRING,
    0,
    CIMPLE_OFF(Test2,ref_field3)
};

extern const Meta_Reference _Test2_ref1;

const Meta_Reference _Test2_ref1 =
{
    CIMPLE_FLAG_REFERENCE,
    "ref1",
    &Test1::static_meta_class,
    CIMPLE_OFF(Test2,ref1)
};

extern const Meta_Reference _Test2_ref2;

const Meta_Reference _Test2_ref2 =
{
    CIMPLE_FLAG_REFERENCE,
    "ref2",
    &Test1::static_meta_class,
    CIMPLE_OFF(Test2,ref2)
};

static Meta_Feature* _Test2_meta_features[] =
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
    CIMPLE_FLAG_ASSOCIATION,
    "Test2",
    _Test2_meta_features,
    CIMPLE_ARRAY_SIZE(_Test2_meta_features),
    sizeof(Test2),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    0, /* num_keys */
    0xDC8273B9,/* crc */
    0,
};

CIMPLE_NAMESPACE_END

