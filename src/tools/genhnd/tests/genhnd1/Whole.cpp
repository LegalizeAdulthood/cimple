/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Whole.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_737F1D2238421FC5AB9BC02831CC9C69;

/*[1302]*/
extern const Meta_Property
_Whole_Key;

/*[1325]*/
const Meta_Property
_Whole_Key =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "Key",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Whole,Key),
    0, /* value */
};

extern const Meta_Reference
_Whole_emb;

/*[1914]*/
const Meta_Reference _Whole_emb =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_EMBEDDED_INSTANCE,
    "emb",
    0, /* meta_qualifiers */
    0, /* num_meta_qualifiers */
    0, /* subscript */
    &Part::static_meta_class,
    CIMPLE_OFF(Whole,emb)
};

/*[2025]*/
static Meta_Feature* _Whole_MFA[] =
{
    (Meta_Feature*)(void*)&_Whole_Key,
    (Meta_Feature*)(void*)&_Whole_emb,
};

/*[2072]*/
static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

/*[2092]*/
const Meta_Class Whole::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Whole",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Whole_MFA,
    CIMPLE_ARRAY_SIZE(_Whole_MFA),
    sizeof(Whole),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    &__meta_repository_737F1D2238421FC5AB9BC02831CC9C69,
};

CIMPLE_NAMESPACE_END

