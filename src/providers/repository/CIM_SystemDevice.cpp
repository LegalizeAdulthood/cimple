//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_SystemDevice.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_48D39CF2E1A81164BA57916E443B1258;

extern const Meta_Reference _CIM_SystemDevice_GroupComponent;

const Meta_Reference _CIM_SystemDevice_GroupComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "GroupComponent",
    &CIM_System::static_meta_class,
    CIMPLE_OFF(CIM_SystemDevice,GroupComponent)
};

extern const Meta_Reference _CIM_SystemDevice_PartComponent;

const Meta_Reference _CIM_SystemDevice_PartComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "PartComponent",
    &CIM_LogicalDevice::static_meta_class,
    CIMPLE_OFF(CIM_SystemDevice,PartComponent)
};

static Meta_Feature* _CIM_SystemDevice_meta_features[] =
{
    (Meta_Feature*)&_CIM_SystemDevice_GroupComponent,
    (Meta_Feature*)&_CIM_SystemDevice_PartComponent,
};

static const char* _super_classes[] =
{
    "CIM_SystemComponent",
    "CIM_Component",
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class CIM_SystemDevice::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_SystemDevice",
    _CIM_SystemDevice_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_SystemDevice_meta_features),
    sizeof(CIM_SystemDevice),
    _locals,
    &CIM_SystemComponent::static_meta_class,
    _super_classes,
    CIMPLE_ARRAY_SIZE(_super_classes),
    2, /* num_keys */
    0xA3654B27,/* crc */
    &__meta_repository_48D39CF2E1A81164BA57916E443B1258,
};

CIMPLE_NAMESPACE_END

