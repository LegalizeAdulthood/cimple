/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "President.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_8F57C0F8B3E5158AA367C7FA50F40F1B;

extern const Meta_Property
_President_Number;

const Meta_Property
_President_Number =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_KEY|CIMPLE_FLAG_READ,
    "Number",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(President,Number),
    0, /* value */
};

extern const Meta_Property
_President_First;

const Meta_Property
_President_First =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "First",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(President,First),
    0, /* value */
};

extern const Meta_Property
_President_Last;

const Meta_Property
_President_Last =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Last",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    STRING,
    0, /* subscript */
    CIMPLE_OFF(President,Last),
    0, /* value */
};

static Meta_Feature* _President_MFA[] =
{
    (Meta_Feature*)&_President_Number,
    (Meta_Feature*)&_President_First,
    (Meta_Feature*)&_President_Last,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
    {1},
};

const Meta_Class President::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "President",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _President_MFA,
    CIMPLE_ARRAY_SIZE(_President_MFA),
    sizeof(President),
    _locals,
    0, /* super_class */ 
    1, /* num_keys */
    0x04EF282E, /* crc */
    &__meta_repository_8F57C0F8B3E5158AA367C7FA50F40F1B,
};

CIMPLE_NAMESPACE_END

