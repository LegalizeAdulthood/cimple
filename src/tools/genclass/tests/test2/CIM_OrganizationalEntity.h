/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#ifndef _cimple_CIM_OrganizationalEntity_h
#define _cimple_CIM_OrganizationalEntity_h

#include <cimple/cimple.h>
#include "CIM_ManagedElement.h"

CIMPLE_NAMESPACE_BEGIN

// CIM_OrganizationalEntity keys:

class CIM_OrganizationalEntity : public Instance
{
public:
    // CIM_ManagedElement features:
    Property<String> Caption;
    Property<String> Description;
    Property<String> ElementName;

    // CIM_OrganizationalEntity features:

    CIMPLE_CLASS(CIM_OrganizationalEntity)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CIM_OrganizationalEntity_h */
