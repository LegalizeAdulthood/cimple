/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#ifndef _cimple_SalesmanLink_h
#define _cimple_SalesmanLink_h

#include <cimple/cimple.h>
#include "PersonLink.h"

CIMPLE_NAMESPACE_BEGIN

// SalesmanLink keys:

class SalesmanLink : public Instance
{
public:
    // PersonLink features:
    Person* parent;
    Person* child;

    // SalesmanLink features:

    CIMPLE_CLASS(SalesmanLink)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_SalesmanLink_h */
