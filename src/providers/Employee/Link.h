/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#ifndef _cimple_Link_h
#define _cimple_Link_h

#include <cimple/cimple.h>
#include "Employee.h"
#include "Manager.h"

CIMPLE_NAMESPACE_BEGIN

// Link keys:

class Link : public Instance
{
public:
    // Link features:
    Employee* Emp;
    Manager* Mgr;

    CIMPLE_CLASS(Link)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Link_h */
