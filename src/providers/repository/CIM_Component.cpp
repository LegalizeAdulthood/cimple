//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_Component.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Reference _CIM_Component_GroupComponent;

const Meta_Reference _CIM_Component_GroupComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "GroupComponent",
    &CIM_ManagedElement::static_meta_class,
    CIMPLE_OFF(CIM_Component,GroupComponent)
};

extern CIMPLE_HIDE const Meta_Reference _CIM_Component_PartComponent;

const Meta_Reference _CIM_Component_PartComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "PartComponent",
    &CIM_ManagedElement::static_meta_class,
    CIMPLE_OFF(CIM_Component,PartComponent)
};

static Meta_Feature* _CIM_Component_meta_features[] =
{
    (Meta_Feature*)&_CIM_Component_GroupComponent,
    (Meta_Feature*)&_CIM_Component_PartComponent,
};

const Meta_Class CIM_Component::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_Component",
    _CIM_Component_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_Component_meta_features),
    sizeof(CIM_Component),
    0,
    2,
    0xD1D41B62,
};

CIMPLE_NAMESPACE_END
