//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_ManagedElement.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Caption;

const Meta_Property _CIM_ManagedElement_Caption =
{
    CIMPLE_FLAG_PROPERTY,
    "Caption",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedElement,Caption)
};

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_Description;

const Meta_Property _CIM_ManagedElement_Description =
{
    CIMPLE_FLAG_PROPERTY,
    "Description",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedElement,Description)
};

extern CIMPLE_HIDE const Meta_Property _CIM_ManagedElement_ElementName;

const Meta_Property _CIM_ManagedElement_ElementName =
{
    CIMPLE_FLAG_PROPERTY,
    "ElementName",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedElement,ElementName)
};

static Meta_Feature* _CIM_ManagedElement_meta_features[] =
{
    (Meta_Feature*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)&_CIM_ManagedElement_ElementName,
};

const Meta_Class CIM_ManagedElement::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_ManagedElement",
    _CIM_ManagedElement_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_ManagedElement_meta_features),
    sizeof(CIM_ManagedElement),
    0,
    0,
    0x5B2A3886,
};

CIMPLE_NAMESPACE_END
