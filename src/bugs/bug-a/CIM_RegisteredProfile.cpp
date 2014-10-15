/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_RegisteredProfile.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_7B1AD485B77E19A58BACB51CE16145E8;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_RegisteredProfile_InstanceID;

const Meta_Property
_CIM_RegisteredProfile_InstanceID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "InstanceID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,InstanceID),
    0, /* value */
};

extern const Meta_Property
_CIM_RegisteredProfile_RegisteredOrganization;

const Meta_Property
_CIM_RegisteredProfile_RegisteredOrganization =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "RegisteredOrganization",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    0, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,RegisteredOrganization),
    0, /* value */
};

extern const Meta_Property
_CIM_RegisteredProfile_OtherRegisteredOrganization;

const Meta_Property
_CIM_RegisteredProfile_OtherRegisteredOrganization =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "OtherRegisteredOrganization",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,OtherRegisteredOrganization),
    0, /* value */
};

extern const Meta_Property
_CIM_RegisteredProfile_RegisteredName;

const Meta_Property
_CIM_RegisteredProfile_RegisteredName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "RegisteredName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,RegisteredName),
    0, /* value */
};

extern const Meta_Property
_CIM_RegisteredProfile_RegisteredVersion;

const Meta_Property
_CIM_RegisteredProfile_RegisteredVersion =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "RegisteredVersion",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,RegisteredVersion),
    0, /* value */
};

extern const Meta_Property
_CIM_RegisteredProfile_AdvertiseTypes;

const Meta_Property
_CIM_RegisteredProfile_AdvertiseTypes =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ|CIMPLE_FLAG_REQUIRED,
    "AdvertiseTypes",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT16,
    -1, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,AdvertiseTypes),
    0, /* value */
};

extern const Meta_Property
_CIM_RegisteredProfile_AdvertiseTypeDescriptions;

const Meta_Property
_CIM_RegisteredProfile_AdvertiseTypeDescriptions =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "AdvertiseTypeDescriptions",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    -1, /* subscript */
    CIMPLE_OFF(CIM_RegisteredProfile,AdvertiseTypeDescriptions),
    0, /* value */
};

static Meta_Feature* _CIM_RegisteredProfile_MFA[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)&_CIM_RegisteredProfile_InstanceID,
    (Meta_Feature*)&_CIM_RegisteredProfile_RegisteredOrganization,
    (Meta_Feature*)&_CIM_RegisteredProfile_OtherRegisteredOrganization,
    (Meta_Feature*)&_CIM_RegisteredProfile_RegisteredName,
    (Meta_Feature*)&_CIM_RegisteredProfile_RegisteredVersion,
    (Meta_Feature*)&_CIM_RegisteredProfile_AdvertiseTypes,
    (Meta_Feature*)&_CIM_RegisteredProfile_AdvertiseTypeDescriptions,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
    {1},
};

const Meta_Class CIM_RegisteredProfile::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "CIM_RegisteredProfile",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_RegisteredProfile_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_RegisteredProfile_MFA),
    sizeof(CIM_RegisteredProfile),
    _locals,
    &CIM_ManagedElement::static_meta_class,
    1, /* num_keys */
    0xB1842599, /* crc */
    &__meta_repository_7B1AD485B77E19A58BACB51CE16145E8,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/bugs/bug-a/CIM_RegisteredProfile.cpp,v 1.4 2007/03/07 20:25:23 mbrasher-public Exp $");
