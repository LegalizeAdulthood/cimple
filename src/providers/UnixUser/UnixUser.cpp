/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "UnixUser.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_5FEAFFEECE6B1504B2F293F9000A7329;

extern const Meta_Property
_UnixUser_name;

const Meta_Property
_UnixUser_name =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "name",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,name),
    0, /* value */
};

extern const Meta_Property
_UnixUser_password;

const Meta_Property
_UnixUser_password =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "password",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,password),
    0, /* value */
};

extern const Meta_Property
_UnixUser_uid;

const Meta_Property
_UnixUser_uid =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "uid",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,uid),
    0, /* value */
};

extern const Meta_Property
_UnixUser_gid;

const Meta_Property
_UnixUser_gid =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "gid",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,gid),
    0, /* value */
};

extern const Meta_Property
_UnixUser_fullName;

const Meta_Property
_UnixUser_fullName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "fullName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,fullName),
    0, /* value */
};

extern const Meta_Property
_UnixUser_homeDir;

const Meta_Property
_UnixUser_homeDir =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "homeDir",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,homeDir),
    0, /* value */
};

extern const Meta_Property
_UnixUser_shellProgram;

const Meta_Property
_UnixUser_shellProgram =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "shellProgram",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(UnixUser,shellProgram),
    0, /* value */
};

static Meta_Feature* _UnixUser_MFA[] =
{
    (Meta_Feature*)(void*)&_UnixUser_name,
    (Meta_Feature*)(void*)&_UnixUser_password,
    (Meta_Feature*)(void*)&_UnixUser_uid,
    (Meta_Feature*)(void*)&_UnixUser_gid,
    (Meta_Feature*)(void*)&_UnixUser_fullName,
    (Meta_Feature*)(void*)&_UnixUser_homeDir,
    (Meta_Feature*)(void*)&_UnixUser_shellProgram,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class UnixUser::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "UnixUser",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _UnixUser_MFA,
    CIMPLE_ARRAY_SIZE(_UnixUser_MFA),
    sizeof(UnixUser),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_5FEAFFEECE6B1504B2F293F9000A7329,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/UnixUser/UnixUser.cpp,v 1.15 2007/04/26 22:41:06 mbrasher-public Exp $");
