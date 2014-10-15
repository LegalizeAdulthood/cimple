//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "SomeClass.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

CIMPLE_HIDE
extern const Meta_Property _SomeClass_prop1;

const Meta_Property _SomeClass_prop1 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop1",
    STRING,
    0,
    CIMPLE_OFF(SomeClass,prop1)
};

CIMPLE_HIDE
extern const Meta_Property _SomeClass_prop2;

const Meta_Property _SomeClass_prop2 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop2",
    UINT32,
    0,
    CIMPLE_OFF(SomeClass,prop2)
};

CIMPLE_HIDE
extern const Meta_Property _SomeClass_prop3;

const Meta_Property _SomeClass_prop3 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop3",
    BOOLEAN,
    0,
    CIMPLE_OFF(SomeClass,prop3)
};

CIMPLE_HIDE
extern const Meta_Property _SomeClass_prop4;

const Meta_Property _SomeClass_prop4 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop4",
    STRING,
    -1,
    CIMPLE_OFF(SomeClass,prop4)
};

CIMPLE_HIDE
extern const Meta_Property _SomeClass_prop5;

const Meta_Property _SomeClass_prop5 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop5",
    UINT32,
    -1,
    CIMPLE_OFF(SomeClass,prop5)
};

CIMPLE_HIDE
extern const Meta_Property _SomeClass_prop6;

const Meta_Property _SomeClass_prop6 =
{
    CIMPLE_FLAG_PROPERTY,
    "prop6",
    BOOLEAN,
    -1,
    CIMPLE_OFF(SomeClass,prop6)
};

CIMPLE_HIDE
extern const Meta_Reference _SomeClass_other1;

const Meta_Reference _SomeClass_other1 =
{
    CIMPLE_FLAG_REFERENCE,
    "other1",
    &OtherClass::static_meta_class,
    CIMPLE_OFF(SomeClass,other1)
};

CIMPLE_HIDE
extern const Meta_Reference _SomeClass_other2;

const Meta_Reference _SomeClass_other2 =
{
    CIMPLE_FLAG_REFERENCE,
    "other2",
    &OtherClass::static_meta_class,
    CIMPLE_OFF(SomeClass,other2)
};

static Meta_Feature* _SomeClass_meta_features[] =
{
    (Meta_Feature*)&_SomeClass_prop1,
    (Meta_Feature*)&_SomeClass_prop2,
    (Meta_Feature*)&_SomeClass_prop3,
    (Meta_Feature*)&_SomeClass_prop4,
    (Meta_Feature*)&_SomeClass_prop5,
    (Meta_Feature*)&_SomeClass_prop6,
    (Meta_Feature*)&_SomeClass_other1,
    (Meta_Feature*)&_SomeClass_other2,
};

const Meta_Class SomeClass::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "SomeClass",
    _SomeClass_meta_features,
    CIMPLE_ARRAY_SIZE(_SomeClass_meta_features),
    sizeof(SomeClass),
    0,
    0,
    0xB0044D87,
};

CIMPLE_NAMESPACE_END

