/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Aristos_RegisteredProfile.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_RegisteredProfile_InstanceID;

extern const Meta_Property
_CIM_RegisteredProfile_RegisteredOrganization;

extern const Meta_Property
_CIM_RegisteredProfile_OtherRegisteredOrganization;

extern const Meta_Property
_CIM_RegisteredProfile_RegisteredName;

extern const Meta_Property
_CIM_RegisteredProfile_RegisteredVersion;

extern const Meta_Property
_CIM_RegisteredProfile_AdvertiseTypes;

extern const Meta_Property
_CIM_RegisteredProfile_AdvertiseTypeDescriptions;

static Meta_Feature* _Aristos_RegisteredProfile_MFA[] =
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
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
};

const Meta_Class Aristos_RegisteredProfile::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Aristos_RegisteredProfile",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Aristos_RegisteredProfile_MFA,
    CIMPLE_ARRAY_SIZE(_Aristos_RegisteredProfile_MFA),
    sizeof(Aristos_RegisteredProfile),
    _locals,
    &CIM_RegisteredProfile::static_meta_class,
    1, /* num_keys */
    0xCF09C65F, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/bugs/bug-a/Aristos_RegisteredProfile.cpp,v 1.2 2007/03/07 20:25:22 mbrasher-public Exp $");
