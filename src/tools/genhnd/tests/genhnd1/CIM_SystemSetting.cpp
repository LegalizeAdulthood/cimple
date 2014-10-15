/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.7
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_SystemSetting.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_SystemSetting_SettingID;

const Meta_Property
_CIM_SystemSetting_SettingID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "SettingID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_SystemSetting,SettingID),
    0, /* value */
};

extern const Meta_Property
_CIM_SystemSetting_SystemCreationClassName;

const Meta_Property
_CIM_SystemSetting_SystemCreationClassName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "SystemCreationClassName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_SystemSetting,SystemCreationClassName),
    0, /* value */
};

extern const Meta_Property
_CIM_SystemSetting_SystemName;

const Meta_Property
_CIM_SystemSetting_SystemName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "SystemName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_SystemSetting,SystemName),
    0, /* value */
};

extern const Meta_Property
_CIM_SystemSetting_CreationClassName;

const Meta_Property
_CIM_SystemSetting_CreationClassName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "CreationClassName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_SystemSetting,CreationClassName),
    0, /* value */
};

static Meta_Feature* _CIM_SystemSetting_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_SystemSetting_SettingID,
    (Meta_Feature*)(void*)&CIM_Setting_VerifyOKToApplyToMSE_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_ApplyToMSE_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_VerifyOKToApplyToCollection_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_ApplyToCollection_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_ApplyIncrementalChangeToMSE_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_method::static_meta_class,
    (Meta_Feature*)(void*)&CIM_Setting_ApplyIncrementalChangeToCollection_method::static_meta_class,
    (Meta_Feature*)(void*)&_CIM_SystemSetting_SystemCreationClassName,
    (Meta_Feature*)(void*)&_CIM_SystemSetting_SystemName,
    (Meta_Feature*)(void*)&_CIM_SystemSetting_CreationClassName,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {1},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_SystemSetting::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_SystemSetting",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_SystemSetting_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_SystemSetting_MFA),
    sizeof(CIM_SystemSetting),
    _locals,
    &CIM_Setting::static_meta_class,
    4, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

