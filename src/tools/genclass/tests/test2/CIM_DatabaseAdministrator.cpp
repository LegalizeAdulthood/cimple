//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#include <cimple/Meta_Class.h>
#include <cimple/Meta_Property.h>
#include <cimple/Meta_Reference.h>
#include "CIM_DatabaseAdministrator.h"

CIMPLE_NAMESPACE_BEGIN

using namespace cimple;

extern CIMPLE_HIDE const Meta_Reference _CIM_DatabaseAdministrator_Antecedent;

const Meta_Reference _CIM_DatabaseAdministrator_Antecedent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "Antecedent",
    &CIM_CommonDatabase::static_meta_class,
    CIMPLE_OFF(CIM_DatabaseAdministrator,Antecedent)
};

extern CIMPLE_HIDE const Meta_Reference _CIM_DatabaseAdministrator_Dependent;

const Meta_Reference _CIM_DatabaseAdministrator_Dependent =
{
    CIMPLE_FLAG_REFERENCE|CIMPLE_FLAG_KEY,
    "Dependent",
    &CIM_UserEntity::static_meta_class,
    CIMPLE_OFF(CIM_DatabaseAdministrator,Dependent)
};

static Meta_Feature* _CIM_DatabaseAdministrator_meta_features[] =
{
    (Meta_Feature*)&_CIM_DatabaseAdministrator_Antecedent,
    (Meta_Feature*)&_CIM_DatabaseAdministrator_Dependent,
};

const Meta_Class CIM_DatabaseAdministrator::static_meta_class =
{
    CIMPLE_FLAG_ASSOCIATION,
    "CIM_DatabaseAdministrator",
    _CIM_DatabaseAdministrator_meta_features,
    CIMPLE_ARRAY_SIZE(_CIM_DatabaseAdministrator_meta_features),
    sizeof(CIM_DatabaseAdministrator),
    &CIM_Dependency::static_meta_class,
    2,
    0xEF2153FB,
    0,
};

CIMPLE_NAMESPACE_END

