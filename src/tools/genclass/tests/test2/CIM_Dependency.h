//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _CIM_Dependency_h
#define _CIM_Dependency_h

#include <cimple/cimple.h>
#include "CIM_ManagedElement.h"
#include "CIM_ManagedElement.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_Dependency : public Instance
{
public:
    // CIM_Dependency features:
    CIM_ManagedElement* Antecedent;
    CIM_ManagedElement* Dependent;

    CIMPLE_CLASS(CIM_Dependency)
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_Dependency_h */