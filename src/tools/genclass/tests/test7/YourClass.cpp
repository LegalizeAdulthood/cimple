/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "YourClass.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_YourClass_str1;

const Meta_Property
_YourClass_str1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "str1",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(YourClass,str1),
    0, /* value */
};

extern const Meta_Property
_YourClass_str2;

const Meta_Property
_YourClass_str2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "str2",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(YourClass,str2),
    0, /* value */
};

extern const Meta_Reference
_YourClass_obj1;

const Meta_Reference _YourClass_obj1 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,
    "obj1",
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* subscript */
    &Instance::static_meta_class,
    CIMPLE_OFF(YourClass,obj1)
};

extern const Meta_Reference
_YourClass_obj2;

const Meta_Reference _YourClass_obj2 =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_OBJECT,
    "obj2",
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* subscript */
    &Instance::static_meta_class,
    CIMPLE_OFF(YourClass,obj2)
};

static Meta_Feature* _YourClass_MFA[] =
{
    (Meta_Feature*)(void*)&_YourClass_str1,
    (Meta_Feature*)(void*)&_YourClass_str2,
    (Meta_Feature*)(void*)&_YourClass_obj1,
    (Meta_Feature*)(void*)&_YourClass_obj2,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class YourClass::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_INDICATION,
    "YourClass",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _YourClass_MFA,
    CIMPLE_ARRAY_SIZE(_YourClass_MFA),
    sizeof(YourClass),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test7/YourClass.cpp,v 1.26 2007/06/19 15:25:04 mbrasher-public Exp $");
