/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_OrganizationalEntity.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

static Meta_Feature* _CIM_OrganizationalEntity_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
};

const Meta_Class CIM_OrganizationalEntity::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_OrganizationalEntity",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_OrganizationalEntity_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_OrganizationalEntity_MFA),
    sizeof(CIM_OrganizationalEntity),
    _locals,
    &CIM_ManagedElement::static_meta_class,
    0, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test2/CIM_OrganizationalEntity.cpp,v 1.23 2007/06/19 15:25:03 mbrasher-public Exp $");
