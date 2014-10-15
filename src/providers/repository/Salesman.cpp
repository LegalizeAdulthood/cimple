//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Salesman.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_E277BAB546AC1F9B84FD3C4B6BE00B1C;

extern const Meta_Property _Person_ssn;

extern const Meta_Property _Person_first;

extern const Meta_Property _Person_last;

extern const Meta_Property _Salesman_budget;

const Meta_Property _Salesman_budget =
{
    CIMPLE_FLAG_PROPERTY,
    "budget",
    UINT32,
    0,
    CIMPLE_OFF(Salesman,budget)
};

static Meta_Feature* _Salesman_meta_features[] =
{
    (Meta_Feature*)&_Person_ssn,
    (Meta_Feature*)&_Person_first,
    (Meta_Feature*)&_Person_last,
    (Meta_Feature*)&_Salesman_budget,
};

const Meta_Class Salesman::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Salesman",
    _Salesman_meta_features,
    CIMPLE_ARRAY_SIZE(_Salesman_meta_features),
    sizeof(Salesman),
    &Person::static_meta_class,
    1,
    0x7EA2FB5C,
    &__meta_repository_E277BAB546AC1F9B84FD3C4B6BE00B1C,
};

CIMPLE_NAMESPACE_END

