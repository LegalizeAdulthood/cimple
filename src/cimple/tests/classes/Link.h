/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 2.0.12
//
//==============================================================================

#ifndef _cimple_Link_h
#define _cimple_Link_h

#include <cimple/cimple.h>
#include "Manager.h"
#include "Employee.h"

CIMPLE_NAMESPACE_BEGIN

// Link keys:

/*[930]*/
class Link : public Instance
{
public:
    // Link features:
    Manager* Mgr;
    Employee* Emp;

    CIMPLE_CLASS(Link)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Link_h */
