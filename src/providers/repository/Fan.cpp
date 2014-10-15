//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Fan.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _Fan_DeviceID;

const Meta_Property _Fan_DeviceID =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY,
    "DeviceID",
    STRING,
    0,
    CIMPLE_OFF(Fan,DeviceID)
};

extern CIMPLE_HIDE const Meta_Property _Fan_Speed;

const Meta_Property _Fan_Speed =
{
    CIMPLE_FLAG_PROPERTY,
    "Speed",
    UINT64,
    0,
    CIMPLE_OFF(Fan,Speed)
};

extern CIMPLE_HIDE const Meta_Property _Fan_DesiredSpeed;

const Meta_Property _Fan_DesiredSpeed =
{
    CIMPLE_FLAG_PROPERTY,
    "DesiredSpeed",
    UINT64,
    0,
    CIMPLE_OFF(Fan,DesiredSpeed)
};

static const Meta_Property _Fan_SetSpeed_DesiredSpeed =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "DesiredSpeed",
    UINT64,
    0,
    CIMPLE_OFF(Fan_SetSpeed_method,DesiredSpeed)
};

static const Meta_Property _Fan_SetSpeed_return_value =
{
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    UINT32,
    0,
    CIMPLE_OFF(Fan_SetSpeed_method,return_value)
};

static Meta_Feature* _Fan_SetSpeed_meta_features[] =
{
    (Meta_Feature*)&_Fan_SetSpeed_DesiredSpeed,
    (Meta_Feature*)&_Fan_SetSpeed_return_value
};

const Meta_Method Fan_SetSpeed_method::static_meta_class =
{
    CIMPLE_FLAG_METHOD,
    "SetSpeed",
    _Fan_SetSpeed_meta_features,
    CIMPLE_ARRAY_SIZE(_Fan_SetSpeed_meta_features),
    sizeof(Fan_SetSpeed_method),
    UINT32,
};

static Meta_Feature* _Fan_meta_features[] =
{
    (Meta_Feature*)&_Fan_DeviceID,
    (Meta_Feature*)&_Fan_Speed,
    (Meta_Feature*)&_Fan_DesiredSpeed,
    (Meta_Feature*)&Fan_SetSpeed_method::static_meta_class,
};

const Meta_Class Fan::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "Fan",
    _Fan_meta_features,
    CIMPLE_ARRAY_SIZE(_Fan_meta_features),
    sizeof(Fan),
    0,
    1,
    0xF0EDE346,
};

CIMPLE_NAMESPACE_END
