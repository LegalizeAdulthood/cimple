/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_LogicalElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_0534992289351A029B38A12919E776DE;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_ManagedSystemElement_InstallDate;

extern const Meta_Property
_CIM_ManagedSystemElement_Name;

extern const Meta_Property
_CIM_ManagedSystemElement_OperationalStatus;

extern const Meta_Property
_CIM_ManagedSystemElement_StatusDescriptions;

extern const Meta_Property
_CIM_ManagedSystemElement_Status;

extern const Meta_Property
_CIM_ManagedSystemElement_HealthState;

static Meta_Feature* _CIM_LogicalElement_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_InstallDate,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_Name,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_OperationalStatus,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_StatusDescriptions,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_Status,
    (Meta_Feature*)(void*)&_CIM_ManagedSystemElement_HealthState,
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
};

const Meta_Class CIM_LogicalElement::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_LogicalElement",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_LogicalElement_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_LogicalElement_MFA),
    sizeof(CIM_LogicalElement),
    _locals,
    &CIM_ManagedSystemElement::static_meta_class,
    0, /* num_keys */
    &__meta_repository_0534992289351A029B38A12919E776DE,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/CIM_DiskDrive/CIM_LogicalElement.cpp,v 1.9 2007/06/19 15:24:56 mbrasher-public Exp $");
