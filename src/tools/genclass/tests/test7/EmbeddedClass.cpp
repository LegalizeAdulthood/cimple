//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "EmbeddedClass.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_EmbeddedClass_msg;

const Meta_Property
_EmbeddedClass_msg =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "msg",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(EmbeddedClass,msg),
    0, /* value */
};

static Meta_Feature* _EmbeddedClass_MFA[] =
{
    (Meta_Feature*)&_EmbeddedClass_msg,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
};

const Meta_Class EmbeddedClass::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "EmbeddedClass",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _EmbeddedClass_MFA,
    CIMPLE_ARRAY_SIZE(_EmbeddedClass_MFA),
    sizeof(EmbeddedClass),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    0xC580D23F, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

