/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "Manager.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Repository __meta_repository_0EF130F9E1041F83800325E3CC83F347;

extern const Meta_Property
_Employee_Id;

extern const Meta_Property
_Employee_First;

extern const Meta_Property
_Employee_Last;

extern const Meta_Property
_Employee_Gender;

extern const Meta_Property
_Employee_Active;

extern const Meta_Property
_Employee_OutOfOffice;

extern const Meta_Property
_Manager_NumEmployees;

const Meta_Property
_Manager_NumEmployees =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "NumEmployees",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Manager,NumEmployees),
    0, /* value */
};

extern const Meta_Property
_Manager_Budget;

const Meta_Property
_Manager_Budget =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_PROPERTY|CIMPLE_FLAG_READ,
    "Budget",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    UINT32,
    0, /* subscript */
    CIMPLE_OFF(Manager,Budget),
    0, /* value */
};

static Meta_Feature* _Manager_MFA[] =
{
    (Meta_Feature*)(void*)&_Employee_Id,
    (Meta_Feature*)(void*)&_Employee_First,
    (Meta_Feature*)(void*)&_Employee_Last,
    (Meta_Feature*)(void*)&_Employee_Gender,
    (Meta_Feature*)(void*)&_Employee_Active,
    (Meta_Feature*)(void*)&_Employee_OutOfOffice,
    (Meta_Feature*)(void*)&Employee_SetOutOfOfficeState_method::static_meta_class,
    (Meta_Feature*)(void*)&Employee_GetEmployeeCount_method::static_meta_class,
    (Meta_Feature*)(void*)&_Manager_NumEmployees,
    (Meta_Feature*)(void*)&_Manager_Budget,
};

static const Meta_Feature_Local _locals[] =
{
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {1},
    {1},
};

const Meta_Class Manager::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_CLASS,
    "Manager",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _Manager_MFA,
    CIMPLE_ARRAY_SIZE(_Manager_MFA),
    sizeof(Manager),
    _locals,
    &Employee::static_meta_class,
    1, /* num_keys */
    &__meta_repository_0EF130F9E1041F83800325E3CC83F347,
};

CIMPLE_NAMESPACE_END

