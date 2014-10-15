/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Link.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Reference
_Link_Mgr;

const Meta_Reference
_Link_Mgr =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "Mgr",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Manager::static_meta_class,
    CIMPLE_OFF(Link,Mgr)
};

extern const Meta_Reference
_Link_Emp;

const Meta_Reference
_Link_Emp =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "Emp",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &Employee::static_meta_class,
    CIMPLE_OFF(Link,Emp)
};

static Meta_Feature* _Link_MFA[] =
{
    (Meta_Feature*)(void*)&_Link_Mgr,
    (Meta_Feature*)(void*)&_Link_Emp,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class Link::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "Link",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Link_MFA,
    CIMPLE_ARRAY_SIZE(_Link_MFA),
    sizeof(Link),
    _locals,
    0, /* super_class */ 
    2, /* num_keys */
    0x4164336D, /* crc */
    0,
};

CIMPLE_NAMESPACE_END

