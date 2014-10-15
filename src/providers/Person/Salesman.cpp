/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 2.1.0
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Salesman.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_CFA0C0C0BF12124090F12E88B029ABDC;

/*[1578]*/
extern const Meta_Property
_Person_ssn;

/*[1578]*/
extern const Meta_Property
_Person_first;

/*[1578]*/
extern const Meta_Property
_Person_last;

/*[1578]*/
extern const Meta_Property
_Salesman_budget;

/*[1601]*/
const Meta_Property
_Salesman_budget =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "budget",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Salesman,budget),
    0, /* value */
};

/*[2301]*/
static Meta_Feature* _Salesman_MFA[] =
{
    (Meta_Feature*)(void*)&_Person_ssn,
    (Meta_Feature*)(void*)&_Person_first,
    (Meta_Feature*)(void*)&_Person_last,
    (Meta_Feature*)(void*)&Person_hello_method::static_meta_class,
    (Meta_Feature*)(void*)&_Salesman_budget,
};

/*[2348]*/
static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {0},
    {1},
};

/*[2368]*/
const Meta_Class Salesman::static_meta_class =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_CLASS,
    "Salesman",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Salesman_MFA,
    CIMPLE_ARRAY_SIZE(_Salesman_MFA),
    sizeof(Salesman),
    _locals,
    &Person::static_meta_class,
    1, /* num_keys */
    &__meta_repository_CFA0C0C0BF12124090F12E88B029ABDC,
};

CIMPLE_NAMESPACE_END

