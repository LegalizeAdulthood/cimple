/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Class1.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_BF07919D97D812EA85A754AAA084E729;

/*[1302]*/
extern const Meta_Property
_Class1_p1;

/*[1325]*/
const Meta_Property
_Class1_p1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "p1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Class1,p1),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Class1_p2;

/*[1325]*/
const Meta_Property
_Class1_p2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "p2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Class1,p2),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Class1_p3;

/*[1325]*/
const Meta_Property
_Class1_p3 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "p3",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0, /* subscript */
    CIMPLE_OFF(Class1,p3),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Class1_p4;

/*[1325]*/
const Meta_Property
_Class1_p4 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "p4",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0, /* subscript */
    CIMPLE_OFF(Class1,p4),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Class1_p5;

/*[1325]*/
const Meta_Property
_Class1_p5 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "p5",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(Class1,p5),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Class1_p6;

/*[1325]*/
const Meta_Property
_Class1_p6 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "p6",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Class1,p6),
    0, /* value */
};

/*[2025]*/
static Meta_Feature* _Class1_MFA[] =
{
    (Meta_Feature*)(void*)&_Class1_p1,
    (Meta_Feature*)(void*)&_Class1_p2,
    (Meta_Feature*)(void*)&_Class1_p3,
    (Meta_Feature*)(void*)&_Class1_p4,
    (Meta_Feature*)(void*)&_Class1_p5,
    (Meta_Feature*)(void*)&_Class1_p6,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

/*[2092]*/
const Meta_Class Class1::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Class1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Class1_MFA,
    CIMPLE_ARRAY_SIZE(_Class1_MFA),
    sizeof(Class1),
    _locals,
    0, /* super_class */ 
    3, /* num_keys */
    &__meta_repository_BF07919D97D812EA85A754AAA084E729,
};

CIMPLE_NAMESPACE_END

