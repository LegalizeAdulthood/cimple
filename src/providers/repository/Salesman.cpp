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

extern const Meta_Repository __meta_repository_7E50A1B19DE218BAB02DA17EE255C350;

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

static const char* _super_classes[] =
{
    "Person",
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {1},
};

const Meta_Class Salesman::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Salesman",
    _Salesman_meta_features,
    CIMPLE_ARRAY_SIZE(_Salesman_meta_features),
    sizeof(Salesman),
    _locals,
    &Person::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    1, /* num_keys */
    0x7EA2FB5C,/* crc */
    &__meta_repository_7E50A1B19DE218BAB02DA17EE255C350,
};

CIMPLE_NAMESPACE_END

