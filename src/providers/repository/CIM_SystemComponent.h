//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _CIM_SystemComponent_h
#define _CIM_SystemComponent_h

#include <cimple/cimple.h>
#include "CIM_Component.h"
#include "CIM_System.h"
#include "CIM_ManagedSystemElement.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE CIM_SystemComponent : public Instance
{
public:
    // CIM_Component features:
    CIM_System* GroupComponent;
    CIM_ManagedSystemElement* PartComponent;

    // CIM_SystemComponent features:

    CIMPLE_CLASS(CIM_SystemComponent)
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_SystemComponent_h */
