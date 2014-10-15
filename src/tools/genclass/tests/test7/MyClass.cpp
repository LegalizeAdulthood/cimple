/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "MyClass.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_YourClass_str1;

extern const Meta_Property
_MyClass_str2;

const Meta_Property
_MyClass_str2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "str2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(MyClass,str2),
    0, /* value */
};

extern const Meta_Reference
_YourClass_obj1;

extern const Meta_Reference
_MyClass_obj2;

const Meta_Reference _MyClass_obj2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,
    "obj2",
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* subscript */
    &Instance::static_meta_class,
    CIMPLE_OFF(MyClass,obj2)
};

extern const Meta_Property
_MyClass_str3;

const Meta_Property
_MyClass_str3 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "str3",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(MyClass,str3),
    0, /* value */
};

extern const Meta_Reference
_MyClass_obj3;

const Meta_Reference _MyClass_obj3 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,
    "obj3",
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* subscript */
    &Instance::static_meta_class,
    CIMPLE_OFF(MyClass,obj3)
};

static Meta_Feature* _MyClass_MFA[] =
{
    (Meta_Feature*)(void*)&_YourClass_str1,
    (Meta_Feature*)(void*)&_MyClass_str2,
    (Meta_Feature*)(void*)&_YourClass_obj1,
    (Meta_Feature*)(void*)&_MyClass_obj2,
    (Meta_Feature*)(void*)&_MyClass_str3,
    (Meta_Feature*)(void*)&_MyClass_obj3,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {1},
    {0},
    {1},
    {1},
    {1},
};

const Meta_Class MyClass::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_INDICATION,
    "MyClass",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _MyClass_MFA,
    CIMPLE_ARRAY_SIZE(_MyClass_MFA),
    sizeof(MyClass),
    _locals,
    &YourClass::static_meta_class,
    0, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test7/MyClass.cpp,v 1.25 2007/04/26 22:41:11 mbrasher-public Exp $");
