//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "A.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _A_a;

const Meta_Property _A_a =
{
    CIMPLE_FLAG_PROPERTY,
    "a",
    UINT32,
    0,
    CIMPLE_OFF(A,a)
};

static Meta_Feature* _A_meta_features[] =
{
    (Meta_Feature*)&_A_a,
};

const Meta_Class A::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "A",
    _A_meta_features,
    CIMPLE_ARRAY_SIZE(_A_meta_features),
    sizeof(A),
    0,
    0,
    0xD1584D4B,
};

CIMPLE_NAMESPACE_END

