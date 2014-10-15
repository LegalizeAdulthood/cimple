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

extern const Meta_Repository __meta_repository_301C3D768E5D1704B1028C1944B9CD9D;

extern CIMPLE_HIDE const Meta_Reference _CIM_SystemDevice_GroupComponent;

const Meta_Reference _CIM_SystemDevice_GroupComponent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "GroupComponent",
    &CIM_System::static_meta_class,
    CIMPLE_OFF(CIM_SystemDevice,GroupComponent)
};

extern CIMPLE_HIDE const Meta_Reference _CIM_SystemDevice_PartComponent;

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

const Meta_Class CIM_SystemDevice::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_SystemDevice",
    _CIM_SystemDevice_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_SystemDevice_meta_features),
    sizeof(CIM_SystemDevice),
    &CIM_SystemComponent::static_meta_class,
    2,
    0xA3654B27,
    &__meta_repository_301C3D768E5D1704B1028C1944B9CD9D,
};

CIMPLE_NAMESPACE_END

