//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_System_h
#define _cimple_CIM_System_h

#include <cimple/cimple.h>
#include "CIM_EnabledLogicalElement.h"

CIMPLE_NAMESPACE_BEGIN

class CIM_System : public Instance
{
public:
    // CIM_ManagedElement features:
    Property<String> Caption;
    Property<String> Description;
    Property<String> ElementName;

    // CIM_ManagedSystemElement features:
    Property<Datetime> InstallDate;
    Property<String> Name;
    Property<Array_uint16> OperationalStatus;
    Property<Array_String> StatusDescriptions;
    Property<String> Status;

    // CIM_LogicalElement features:

    // CIM_EnabledLogicalElement features:
    Property<uint16> EnabledState;
    Property<String> OtherEnabledState;
    Property<uint16> RequestedState;
    Property<uint16> EnabledDefault;
    Property<Datetime> TimeOfLastStateChange;

    // CIM_System features:
    Property<String> CreationClassName;
    Property<String> NameFormat;
    Property<String> PrimaryOwnerName;
    Property<String> PrimaryOwnerContact;
    Property<Array_String> Roles;

    CIMPLE_CLASS(CIM_System)
};

typedef CIM_EnabledLogicalElement_RequestStateChange_method CIM_System_RequestStateChange_method;

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_System_h */
