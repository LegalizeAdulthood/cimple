/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_RedundancySet_h
#define _cimple_CIM_RedundancySet_h

#include <cimple/cimple.h>
#include "CIM_SystemSpecificCollection.h"
#include "CIM_ManagedElement.h"
#include "CIM_ManagedElement.h"

#if (0x00633300 > CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.51) is newer than the version of <cimple/cimple.h> found on the include path. Please place the matching version of <cimple/cimple.h> on the include path."
#endif

#if (0x00633300 < CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.51) is older than the version of <cimple/cimple.h> found on the include path. Please regenerate the sources with the matching version of genclass."
#endif


CIMPLE_NAMESPACE_BEGIN

class CIM_RedundancySet : public Instance
{
public:
    // CIM_ManagedElement features:
    Property<String> Caption;
    Property<String> Description;
    Property<String> ElementName;

    // CIM_Collection features:

    // CIM_SystemSpecificCollection features:
    Property<String> InstanceID; // KEY

    // CIM_RedundancySet features:
    Property<uint16> RedundancyStatus;
    Property<Array_uint16> TypeOfSet;
    Property<uint32> MinNumberNeeded;
    Property<uint32> MaxNumberSupported;
    Property<String> VendorIdentifyingInfo;
    Property<Array_String> OtherTypeOfSet;
    Property<uint16> LoadBalanceAlgorithm;
    Property<String> OtherLoadBalanceAlgorithm;

    CIMPLE_CLASS(CIM_RedundancySet)
};

class CIM_RedundancySet_Failover_method : public Instance
{
public:
    CIM_ManagedElement* FailoverFrom;
    CIM_ManagedElement* FailoverTo;
    Property<uint32> return_value;
    CIMPLE_METHOD(CIM_RedundancySet_Failover_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_RedundancySet_h */
