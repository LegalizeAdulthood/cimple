/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "MyEmbeddedClass.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_FA4A59197E071AD1B480ECF1C799A5B7;

extern const Meta_Property
_MyEmbeddedClass_msg;

const Meta_Property
_MyEmbeddedClass_msg =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "msg",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(MyEmbeddedClass,msg),
    0, /* value */
};

static Meta_Feature* _MyEmbeddedClass_MFA[] =
{
    (Meta_Feature*)(void*)&_MyEmbeddedClass_msg,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class MyEmbeddedClass::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "MyEmbeddedClass",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _MyEmbeddedClass_MFA,
    CIMPLE_ARRAY_SIZE(_MyEmbeddedClass_MFA),
    sizeof(MyEmbeddedClass),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    &__meta_repository_FA4A59197E071AD1B480ECF1C799A5B7,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MyIndication/MyEmbeddedClass.cpp,v 1.9 2007/04/26 22:41:05 mbrasher-public Exp $");
