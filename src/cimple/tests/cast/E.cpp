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

extern CIMPLE_HIDE const Meta_Property _E_e;

const Meta_Property _E_e =
{
    CIMPLE_FLAG_PROPERTY,
    "e",
    UINT32,
    0,
    CIMPLE_OFF(E,e)
};

static Meta_Feature* _E_meta_features[] =
{
    (Meta_Feature*)&_E_e,
};

const Meta_Class E::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "E",
    _E_meta_features,
    CIMPLE_ARRAY_SIZE(_E_meta_features),
    sizeof(E),
    0,
    0,
    0x40B42E8F,
};

CIMPLE_NAMESPACE_END
