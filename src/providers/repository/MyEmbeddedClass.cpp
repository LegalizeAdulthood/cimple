//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "MyEmbeddedClass.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_301C3D768E5D1704B1028C1944B9CD9D;

extern CIMPLE_HIDE const Meta_Property _MyEmbeddedClass_msg;

const Meta_Property _MyEmbeddedClass_msg =
{
    CIMPLE_FLAG_PROPERTY,
    "msg",
    STRING,
    0,
    CIMPLE_OFF(MyEmbeddedClass,msg)
};

static Meta_Feature* _MyEmbeddedClass_meta_features[] =
{
    (Meta_Feature*)&_MyEmbeddedClass_msg,
};

const Meta_Class MyEmbeddedClass::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "MyEmbeddedClass",
    _MyEmbeddedClass_meta_features,
    CIMPLE_ARRAY_SIZE(_MyEmbeddedClass_meta_features),
    sizeof(MyEmbeddedClass),
    0,
    0,
    0x6055EE67,
    &__meta_repository_301C3D768E5D1704B1028C1944B9CD9D,
};

CIMPLE_NAMESPACE_END

