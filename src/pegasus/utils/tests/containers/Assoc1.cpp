/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Assoc1.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_BF07919D97D812EA85A754AAA084E729;

/*[1387]*/
extern const Meta_Reference
_Assoc1_left;

/*[1398]*/
const Meta_Reference
_Assoc1_left =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Class1::static_meta_class,
    CIMPLE_OFF(Assoc1,left)
};

/*[1387]*/
extern const Meta_Reference
_Assoc1_right;

/*[1398]*/
const Meta_Reference
_Assoc1_right =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "right",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Class1::static_meta_class,
    CIMPLE_OFF(Assoc1,right)
};

/*[2025]*/
static Meta_Feature* _Assoc1_MFA[] =
{
    (Meta_Feature*)(void*)&_Assoc1_left,
    (Meta_Feature*)(void*)&_Assoc1_right,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

/*[2092]*/
const Meta_Class Assoc1::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "Assoc1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Assoc1_MFA,
    CIMPLE_ARRAY_SIZE(_Assoc1_MFA),
    sizeof(Assoc1),
    _locals,
    0, /* super_class */ 
    2, /* num_keys */
    &__meta_repository_BF07919D97D812EA85A754AAA084E729,
};

CIMPLE_NAMESPACE_END

