//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_OrganizationalEntity.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property _CIM_ManagedElement_Caption;

extern const Meta_Property _CIM_ManagedElement_Description;

extern const Meta_Property _CIM_ManagedElement_ElementName;

static Meta_Feature* _CIM_OrganizationalEntity_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
};

const Meta_Class CIM_OrganizationalEntity::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_OrganizationalEntity",
    _CIM_OrganizationalEntity_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_OrganizationalEntity_meta_features),
    sizeof(CIM_OrganizationalEntity),
    &CIM_ManagedElement::static_meta_class,
    0,
    0x4540D7DA,
    0,
};

CIMPLE_NAMESPACE_END

