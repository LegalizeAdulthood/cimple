/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Hello.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_1EF8761F95D6132EAF6BDA50670F490B;

extern const Meta_Property
_Hello_Key;

const Meta_Property
_Hello_Key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "Key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Hello,Key),
    0, /* value */
};

extern const Meta_Property
_Hello_Message;

const Meta_Property
_Hello_Message =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Message",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(Hello,Message),
    0, /* value */
};

static Meta_Feature* _Hello_MFA[] =
{
    (Meta_Feature*)(void*)&_Hello_Key,
    (Meta_Feature*)(void*)&_Hello_Message,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class Hello::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Hello",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Hello_MFA,
    CIMPLE_ARRAY_SIZE(_Hello_MFA),
    sizeof(Hello),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    0xBE363E9A, /* crc */
    &__meta_repository_1EF8761F95D6132EAF6BDA50670F490B,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Hello/Hello.cpp,v 1.1 2007/03/30 18:51:59 mbrasher-public Exp $");
