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

extern const Meta_Repository __meta_repository_75E2CB8B53E2155E90DBB99ABED114CA;

extern const Meta_Property _CIM_ManagedElement_Caption;

const Meta_Property _CIM_ManagedElement_Caption =
{
    CIMPLE_FLAG_PROPERTY,
    "Caption",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedElement,Caption)
};

extern const Meta_Property _CIM_ManagedElement_Description;

const Meta_Property _CIM_ManagedElement_Description =
{
    CIMPLE_FLAG_PROPERTY,
    "Description",
    STRING,
    0,
    CIMPLE_OFF(CIM_ManagedElement,Description)
};

extern const Meta_Property _CIM_ManagedElement_ElementName;

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

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
};

const Meta_Class CIM_ManagedElement::static_meta_class =
{
    CIMPLE_FLAG_CLASS,
    "CIM_ManagedElement",
    _CIM_ManagedElement_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_ManagedElement_meta_features),
    sizeof(CIM_ManagedElement),
    _locals,
    0, /* super_class */ 
    0, /* super_classes */
    0, /* num_super_classes */
    0, /* num_keys */
    0x5B2A3886,/* crc */
    &__meta_repository_75E2CB8B53E2155E90DBB99ABED114CA,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/pegasus/benchmark/Create1/CIM_ManagedElement.cpp,v 1.2 2007/03/07 20:24:08 mbrasher-public Exp $");
