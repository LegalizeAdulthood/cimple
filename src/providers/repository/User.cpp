//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "User.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_7E50A1B19DE218BAB02DA17EE255C350;

extern const Meta_Property _User_name;

const Meta_Property _User_name =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "name",
    STRING,
    0,
    CIMPLE_OFF(User,name)
};

extern const Meta_Property _User_password;

const Meta_Property _User_password =
{
    CIMPLE_FLAG_PROPERTY,
    "password",
    STRING,
    0,
    CIMPLE_OFF(User,password)
};

extern const Meta_Property _User_uid;

const Meta_Property _User_uid =
{
    CIMPLE_FLAG_PROPERTY,
    "uid",
    UINT32,
    0,
    CIMPLE_OFF(User,uid)
};

extern const Meta_Property _User_gid;

const Meta_Property _User_gid =
{
    CIMPLE_FLAG_PROPERTY,
    "gid",
    UINT32,
    0,
    CIMPLE_OFF(User,gid)
};

extern const Meta_Property _User_fullName;

const Meta_Property _User_fullName =
{
    CIMPLE_FLAG_PROPERTY,
    "fullName",
    STRING,
    0,
    CIMPLE_OFF(User,fullName)
};

extern const Meta_Property _User_homeDir;

const Meta_Property _User_homeDir =
{
    CIMPLE_FLAG_PROPERTY,
    "homeDir",
    STRING,
    0,
    CIMPLE_OFF(User,homeDir)
};

extern const Meta_Property _User_shellProgram;

const Meta_Property _User_shellProgram =
{
    CIMPLE_FLAG_PROPERTY,
    "shellProgram",
    STRING,
    0,
    CIMPLE_OFF(User,shellProgram)
};

static Meta_Feature* _User_meta_features[] =
{
    (Meta_Feature*)&_User_name,
    (Meta_Feature*)&_User_password,
    (Meta_Feature*)&_User_uid,
    (Meta_Feature*)&_User_gid,
    (Meta_Feature*)&_User_fullName,
    (Meta_Feature*)&_User_homeDir,
    (Meta_Feature*)&_User_shellProgram,
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

const Meta_Class User::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "User",
    _User_meta_features,
    CIMPLE_ARRAY_SIZE(_User_meta_features),
    sizeof(User),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    1, /* num_keys */
    0x559C9FCB,/* crc */
    &__meta_repository_7E50A1B19DE218BAB02DA17EE255C350,
};

CIMPLE_NAMESPACE_END

