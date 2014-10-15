/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.7
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_CollectionOfMSEs.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Property
_CIM_ManagedElement_Caption;

extern const Meta_Property
_CIM_ManagedElement_Description;

extern const Meta_Property
_CIM_ManagedElement_ElementName;

extern const Meta_Property
_CIM_CollectionOfMSEs_CollectionID;

const Meta_Property
_CIM_CollectionOfMSEs_CollectionID =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "CollectionID",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(CIM_CollectionOfMSEs,CollectionID),
    0, /* value */
};

static Meta_Feature* _CIM_CollectionOfMSEs_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Caption,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_Description,
    (Meta_Feature*)(void*)&_CIM_ManagedElement_ElementName,
    (Meta_Feature*)(void*)&_CIM_CollectionOfMSEs_CollectionID,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {1},
};

const Meta_Class CIM_CollectionOfMSEs::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS|CIMPLE_FLAG_ABSTRACT,
    "CIM_CollectionOfMSEs",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_CollectionOfMSEs_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_CollectionOfMSEs_MFA),
    sizeof(CIM_CollectionOfMSEs),
    _locals,
    &CIM_Collection::static_meta_class,
    0, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genhnd/tests/genhnd1/CIM_CollectionOfMSEs.cpp,v 1.5 2007/06/26 20:46:54 mbrasher-public Exp $");
