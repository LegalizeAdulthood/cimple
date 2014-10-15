/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Example.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_C7BF6C6FB00317A9BC783810AA2DB41F;

/*[1302]*/
extern const Meta_Property
_Example_key;

/*[1325]*/
const Meta_Property
_Example_key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Example,key),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Example_prop1;

/*[1325]*/
const Meta_Property
_Example_prop1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "prop1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Example,prop1),
    0, /* value */
};

/*[1302]*/
extern const Meta_Property
_Example_prop2;

/*[1325]*/
const Meta_Property
_Example_prop2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "prop2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0, /* subscript */
    CIMPLE_OFF(Example,prop2),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_Example_foo0_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Example_foo0_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Example_foo0_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_foo0_return_value
};

/*[1847]*/
const Meta_Method
Example_foo0_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo0",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_foo0_MFA,
    CIMPLE_ARRAY_SIZE(_Example_foo0_MFA),
    sizeof(Example_foo0_method),
    UINT32,
};

/*[1516]*/
static const Meta_Property
_Example_foo1_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0,
    CIMPLE_OFF(Example_foo1_method,x),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_Example_foo1_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Example_foo1_method,y),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_Example_foo1_z =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "z",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(Example_foo1_method,z),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_Example_foo1_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Example_foo1_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Example_foo1_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_foo1_x,
    (Meta_Feature*)(void*)&_Example_foo1_y,
    (Meta_Feature*)(void*)&_Example_foo1_z,
    (Meta_Feature*)(void*)&_Example_foo1_return_value
};

/*[1847]*/
const Meta_Method
Example_foo1_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_foo1_MFA,
    CIMPLE_ARRAY_SIZE(_Example_foo1_MFA),
    sizeof(Example_foo1_method),
    UINT32,
};

/*[1516]*/
static const Meta_Property
_Example_foo2_w =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "w",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Example_foo2_method,w),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_Example_foo2_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    0,
    CIMPLE_OFF(Example_foo2_method,x),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_Example_foo2_y =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "y",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Example_foo2_method,y),
    0, /* value */
};

/*[1516]*/
static const Meta_Property
_Example_foo2_z =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "z",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    BOOLEAN,
    0,
    CIMPLE_OFF(Example_foo2_method,z),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_Example_foo2_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(Example_foo2_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Example_foo2_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_foo2_w,
    (Meta_Feature*)(void*)&_Example_foo2_x,
    (Meta_Feature*)(void*)&_Example_foo2_y,
    (Meta_Feature*)(void*)&_Example_foo2_z,
    (Meta_Feature*)(void*)&_Example_foo2_return_value
};

/*[1847]*/
const Meta_Method
Example_foo2_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_foo2_MFA,
    CIMPLE_ARRAY_SIZE(_Example_foo2_MFA),
    sizeof(Example_foo2_method),
    UINT32,
};

/*[1669]*/
static const Meta_Property
_Example_foo3_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Example_foo3_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Example_foo3_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_foo3_return_value
};

/*[1847]*/
const Meta_Method
Example_foo3_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo3",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_foo3_MFA,
    CIMPLE_ARRAY_SIZE(_Example_foo3_MFA),
    sizeof(Example_foo3_method),
    STRING,
};

/*[1516]*/
static const Meta_Property
_Example_foo4_x =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "x",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    REAL32,
    -1,
    CIMPLE_OFF(Example_foo4_method,x),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_Example_foo4_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Example_foo4_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Example_foo4_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_foo4_x,
    (Meta_Feature*)(void*)&_Example_foo4_return_value
};

/*[1847]*/
const Meta_Method
Example_foo4_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo4",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_foo4_MFA,
    CIMPLE_ARRAY_SIZE(_Example_foo4_MFA),
    sizeof(Example_foo4_method),
    STRING,
};

/*[1455]*/
static const Meta_Reference
_Example_foo5_house =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_IN,
    "house",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &House::static_meta_class,
    CIMPLE_OFF(Example_foo5_method,house)
};

/*[1669]*/
static const Meta_Property
_Example_foo5_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0,
    CIMPLE_OFF(Example_foo5_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _Example_foo5_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_foo5_house,
    (Meta_Feature*)(void*)&_Example_foo5_return_value
};

/*[1847]*/
const Meta_Method
Example_foo5_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD,
    "foo5",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_foo5_MFA,
    CIMPLE_ARRAY_SIZE(_Example_foo5_MFA),
    sizeof(Example_foo5_method),
    STRING,
};

/*[2025]*/
static Meta_Feature* _Example_MFA[] =
{
    (Meta_Feature*)(void*)&_Example_key,
    (Meta_Feature*)(void*)&_Example_prop1,
    (Meta_Feature*)(void*)&_Example_prop2,
    (Meta_Feature*)(void*)&Example_foo0_method::static_meta_class,
    (Meta_Feature*)(void*)&Example_foo1_method::static_meta_class,
    (Meta_Feature*)(void*)&Example_foo2_method::static_meta_class,
    (Meta_Feature*)(void*)&Example_foo3_method::static_meta_class,
    (Meta_Feature*)(void*)&Example_foo4_method::static_meta_class,
    (Meta_Feature*)(void*)&Example_foo5_method::static_meta_class,
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
    {1},
    {1},
    {1},
};

/*[2092]*/
const Meta_Class Example::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Example",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Example_MFA,
    CIMPLE_ARRAY_SIZE(_Example_MFA),
    sizeof(Example),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_C7BF6C6FB00317A9BC783810AA2DB41F,
};

CIMPLE_NAMESPACE_END

