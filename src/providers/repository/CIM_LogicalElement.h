/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_CIM_LogicalElement_h
#define _cimple_CIM_LogicalElement_h

#include <cimple/cimple.h>
#include "CIM_ManagedSystemElement.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE CIM_LogicalElement : public Instance
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

    CIMPLE_CLASS(CIM_LogicalElement)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_LogicalElement_h */
