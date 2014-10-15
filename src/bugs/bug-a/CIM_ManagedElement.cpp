/*NOCHKSRC*/
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

extern const Meta_Repository __meta_repository_7B1AD485B77E19A58BACB51CE16145E8;

extern const Meta_Property
_CIM_ManagedElement_Caption;

const Meta_Property
_CIM_ManagedElement_Caption =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Caption",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ManagedElement,Caption),
    0, /* value */
};

extern const Meta_Property
_CIM_ManagedElement_Description;

const Meta_Property
_CIM_ManagedElement_Description =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Description",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ManagedElement,Description),
    0, /* value */
};

extern const Meta_Property
_CIM_ManagedElement_ElementName;

const Meta_Property
_CIM_ManagedElement_ElementName =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "ElementName",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_ManagedElement,ElementName),
    0, /* value */
};

static Meta_Feature* _CIM_ManagedElement_MFA[] =
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
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_ManagedElement",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_ManagedElement_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_ManagedElement_MFA),
    sizeof(CIM_ManagedElement),
    _locals,
    0, /* super_class */ 
    0, /* num_keys */
    0x5B2A3886, /* crc */
    &__meta_repository_7B1AD485B77E19A58BACB51CE16145E8,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/bugs/bug-a/CIM_ManagedElement.cpp,v 1.4 2007/03/07 20:25:23 mbrasher-public Exp $");
