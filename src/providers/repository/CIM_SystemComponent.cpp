//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_SystemComponent.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Reference _CIM_SystemComponent_GroupComponent;

const Meta_Reference _CIM_SystemComponent_GroupComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "GroupComponent",
    &CIM_System::static_meta_class,
    CIMPLE_OFF(CIM_SystemComponent,GroupComponent)
};

extern CIMPLE_HIDE const Meta_Reference _CIM_SystemComponent_PartComponent;

const Meta_Reference _CIM_SystemComponent_PartComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "PartComponent",
    &CIM_ManagedSystemElement::static_meta_class,
    CIMPLE_OFF(CIM_SystemComponent,PartComponent)
};

static Meta_Feature* _CIM_SystemComponent_meta_features[] =
{
    (Meta_Feature*)&_CIM_SystemComponent_GroupComponent,
    (Meta_Feature*)&_CIM_SystemComponent_PartComponent,
};

const Meta_Class CIM_SystemComponent::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_SystemComponent",
    _CIM_SystemComponent_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_SystemComponent_meta_features),
    sizeof(CIM_SystemComponent),
    &CIM_Component::static_meta_class,
    2,
    0xB30B108B,
};

CIMPLE_NAMESPACE_END

