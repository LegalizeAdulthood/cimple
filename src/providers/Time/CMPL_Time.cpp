/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CMPL_Time.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_E0E6636F65E11183A24DFA557EADB277;

/*[1516]*/
static const Meta_Property
_CMPL_Time_SetTime_Time =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_IN,
    "Time",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CMPL_Time_SetTime_method,Time),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_CMPL_Time_SetTime_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CMPL_Time_SetTime_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _CMPL_Time_SetTime_MFA[] =
{
    (Meta_Feature*)(void*)&_CMPL_Time_SetTime_Time,
    (Meta_Feature*)(void*)&_CMPL_Time_SetTime_return_value
};

/*[1847]*/
const Meta_Method
CMPL_Time_SetTime_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD|CIMPLE_FLAG_STATIC,
    "SetTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CMPL_Time_SetTime_MFA,
    CIMPLE_ARRAY_SIZE(_CMPL_Time_SetTime_MFA),
    sizeof(CMPL_Time_SetTime_method),
    UINT32,
};

/*[1516]*/
static const Meta_Property
_CMPL_Time_GetTime_Time =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "Time",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    DATETIME,
    0,
    CIMPLE_OFF(CMPL_Time_GetTime_method,Time),
    0, /* value */
};

/*[1669]*/
static const Meta_Property
_CMPL_Time_GetTime_return_value =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_OUT,
    "return_value",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0,
    CIMPLE_OFF(CMPL_Time_GetTime_method,return_value),
    0, /* value */
};

/*[1645]*/
static Meta_Feature* _CMPL_Time_GetTime_MFA[] =
{
    (Meta_Feature*)(void*)&_CMPL_Time_GetTime_Time,
    (Meta_Feature*)(void*)&_CMPL_Time_GetTime_return_value
};

/*[1847]*/
const Meta_Method
CMPL_Time_GetTime_method::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_METHOD|CIMPLE_FLAG_STATIC,
    "GetTime",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CMPL_Time_GetTime_MFA,
    CIMPLE_ARRAY_SIZE(_CMPL_Time_GetTime_MFA),
    sizeof(CMPL_Time_GetTime_method),
    UINT32,
};

/*[2025]*/
static Meta_Feature* _CMPL_Time_MFA[] =
{
    (Meta_Feature*)(void*)&CMPL_Time_SetTime_method::static_meta_class,
    (Meta_Feature*)(void*)&CMPL_Time_GetTime_method::static_meta_class,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

/*[2092]*/
const Meta_Class CMPL_Time::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CMPL_Time",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CMPL_Time_MFA,
    CIMPLE_ARRAY_SIZE(_CMPL_Time_MFA),
    sizeof(CMPL_Time),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    &__meta_repository_E0E6636F65E11183A24DFA557EADB277,
};

CIMPLE_NAMESPACE_END

