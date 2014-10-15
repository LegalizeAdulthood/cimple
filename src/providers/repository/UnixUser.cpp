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

extern CIMPLE_HIDE const Meta_Property _UnixUser_name;

const Meta_Property _UnixUser_name =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "name",
    STRING,
    0,
    CIMPLE_OFF(UnixUser,name)
};

extern CIMPLE_HIDE const Meta_Property _UnixUser_password;

const Meta_Property _UnixUser_password =
{
    CIMPLE_FLAG_PROPERTY,
    "password",
    STRING,
    0,
    CIMPLE_OFF(UnixUser,password)
};

extern CIMPLE_HIDE const Meta_Property _UnixUser_uid;

const Meta_Property _UnixUser_uid =
{
    CIMPLE_FLAG_PROPERTY,
    "uid",
    UINT32,
    0,
    CIMPLE_OFF(UnixUser,uid)
};

extern CIMPLE_HIDE const Meta_Property _UnixUser_gid;

const Meta_Property _UnixUser_gid =
{
    CIMPLE_FLAG_PROPERTY,
    "gid",
    UINT32,
    0,
    CIMPLE_OFF(UnixUser,gid)
};

extern CIMPLE_HIDE const Meta_Property _UnixUser_fullName;

const Meta_Property _UnixUser_fullName =
{
    CIMPLE_FLAG_PROPERTY,
    "fullName",
    STRING,
    0,
    CIMPLE_OFF(UnixUser,fullName)
};

extern CIMPLE_HIDE const Meta_Property _UnixUser_homeDir;

const Meta_Property _UnixUser_homeDir =
{
    CIMPLE_FLAG_PROPERTY,
    "homeDir",
    STRING,
    0,
    CIMPLE_OFF(UnixUser,homeDir)
};

extern CIMPLE_HIDE const Meta_Property _UnixUser_shellProgram;

const Meta_Property _UnixUser_shellProgram =
{
    CIMPLE_FLAG_PROPERTY,
    "shellProgram",
    STRING,
    0,
    CIMPLE_OFF(UnixUser,shellProgram)
};

static Meta_Feature* _UnixUser_meta_features[] =
{
    (Meta_Feature*)&_UnixUser_name,
    (Meta_Feature*)&_UnixUser_password,
    (Meta_Feature*)&_UnixUser_uid,
    (Meta_Feature*)&_UnixUser_gid,
    (Meta_Feature*)&_UnixUser_fullName,
    (Meta_Feature*)&_UnixUser_homeDir,
    (Meta_Feature*)&_UnixUser_shellProgram,
};

const Meta_Class UnixUser::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "UnixUser",
    _UnixUser_meta_features,
    CIMPLE_ARRAY_SIZE(_UnixUser_meta_features),
    sizeof(UnixUser),
    0,
    1,
    0xFBD88476,
};

CIMPLE_NAMESPACE_END

