/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_DatabaseAdministrator.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern const Meta_Reference
_CIM_DatabaseAdministrator_Antecedent;

const Meta_Reference
_CIM_DatabaseAdministrator_Antecedent =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "Antecedent",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_CommonDatabase::static_meta_class,
    CIMPLE_OFF(CIM_DatabaseAdministrator,Antecedent)
};

extern const Meta_Reference
_CIM_DatabaseAdministrator_Dependent;

const Meta_Reference
_CIM_DatabaseAdministrator_Dependent =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "Dependent",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    0, /* subscript */
    &CIM_UserEntity::static_meta_class,
    CIMPLE_OFF(CIM_DatabaseAdministrator,Dependent)
};

static Meta_Feature* _CIM_DatabaseAdministrator_MFA[] =
{
    (Meta_Feature*)(void*)&_CIM_DatabaseAdministrator_Antecedent,
    (Meta_Feature*)(void*)&_CIM_DatabaseAdministrator_Dependent,
};

static const Meta_Feature_Local _locals[] =
{
    {1},
    {1},
};

const Meta_Class CIM_DatabaseAdministrator::static_meta_class =
{
    { 0 }, /* refs */
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_DatabaseAdministrator",
    0, /* meta_qualifiers */
    0, /* num_meta_qaulifiers */
    _CIM_DatabaseAdministrator_MFA,
    CIMPLE_ARRAY_SIZE(_CIM_DatabaseAdministrator_MFA),
    sizeof(CIM_DatabaseAdministrator),
    _locals,
    &CIM_Dependency::static_meta_class,
    2, /* num_keys */
    0,
};

CIMPLE_NAMESPACE_END

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/genclass/tests/test2/CIM_DatabaseAdministrator.cpp,v 1.24 2007/06/19 15:25:02 mbrasher-public Exp $");
