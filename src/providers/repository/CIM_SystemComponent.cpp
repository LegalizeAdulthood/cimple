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

extern const Meta_Repository __meta_repository_B91863F7A56D16BB82F3EE00F1B6B434;

extern const Meta_Reference _CIM_SystemComponent_GroupComponent;

const Meta_Reference _CIM_SystemComponent_GroupComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "GroupComponent",
    &CIM_System::static_meta_class,
    CIMPLE_OFF(CIM_SystemComponent,GroupComponent)
};

extern const Meta_Reference _CIM_SystemComponent_PartComponent;

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

static const char* _super_classes[] =
{
    "CIM_Component",
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class CIM_SystemComponent::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_SystemComponent",
    _CIM_SystemComponent_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_SystemComponent_meta_features),
    sizeof(CIM_SystemComponent),
    _locals,
    &CIM_Component::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    2, /* num_keys */
    0xB30B108B,/* crc */
    &__meta_repository_B91863F7A56D16BB82F3EE00F1B6B434,
};

CIMPLE_NAMESPACE_END

