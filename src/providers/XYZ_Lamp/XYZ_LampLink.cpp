/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "XYZ_LampLink.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_746D0B723EE11A558161C0726C1C928A;

/*[1387]*/
extern const Meta_Reference
_XYZ_LampLink_left;

/*[1398]*/
const Meta_Reference
_XYZ_LampLink_left =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "left",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &XYZ_Lamp::static_meta_class,
    CIMPLE_OFF(XYZ_LampLink,left)
};

/*[1387]*/
extern const Meta_Reference
_XYZ_LampLink_right;

/*[1398]*/
const Meta_Reference
_XYZ_LampLink_right =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "right",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &XYZ_Lamp::static_meta_class,
    CIMPLE_OFF(XYZ_LampLink,right)
};

/*[2025]*/
static Meta_Feature* _XYZ_LampLink_MFA[] =
{
    (Meta_Feature*)(void*)&_XYZ_LampLink_left,
    (Meta_Feature*)(void*)&_XYZ_LampLink_right,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

/*[2092]*/
const Meta_Class XYZ_LampLink::static_meta_class =
{
    CIMPLE_ATOMIC_INITIALIZER, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "XYZ_LampLink",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _XYZ_LampLink_MFA,
    CIMPLE_ARRAY_SIZE(_XYZ_LampLink_MFA),
    sizeof(XYZ_LampLink),
    _locals,
    0, /* super_class */ 
    2, /* num_keys */
    &__meta_repository_746D0B723EE11A558161C0726C1C928A,
};

CIMPLE_NAMESPACE_END

