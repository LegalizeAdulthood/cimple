//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_ComputerSystemDiskDrive_h
#define _cimple_ComputerSystemDiskDrive_h

#include <cimple/cimple.h>
#include "CIM_SystemDevice.h"
#include "ComputerSystem.h"
#include "DiskDrive.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE ComputerSystemDiskDrive : public Instance
{
public:
    // CIM_Component features:
    ComputerSystem* GroupComponent;
    DiskDrive* PartComponent;

    // CIM_SystemComponent features:

    // CIM_SystemDevice features:

    // ComputerSystemDiskDrive features:

    CIMPLE_CLASS(ComputerSystemDiskDrive)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_ComputerSystemDiskDrive_h */
