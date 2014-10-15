/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_SystemDevice_h
#define _cimple_CIM_SystemDevice_h

#include <cimple/cimple.h>
#include "CIM_SystemComponent.h"
#include "CIM_System.h"
#include "CIM_LogicalDevice.h"

CIMPLE_NAMESPACE_BEGIN

// CIM_SystemDevice keys:

class CIM_SystemDevice : public Instance
{
public:
    // CIM_Component features:
    CIM_System* GroupComponent;
    CIM_LogicalDevice* PartComponent;

    // CIM_SystemComponent features:

    // CIM_SystemDevice features:

    CIMPLE_CLASS(CIM_SystemDevice)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_SystemDevice_h */
