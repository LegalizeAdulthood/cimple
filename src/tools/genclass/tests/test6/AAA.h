//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _AAA_h
#define _AAA_h

#include <cimple/cimple.h>
#include "CCC.h"
#include "DDD.h"
#include "CCC.h"

CIMPLE_NAMESPACE_BEGIN

class AAA : public Instance
{
public:
    // AAA features:
    CCC* left;
    DDD* right;

    CIMPLE_CLASS(AAA)
};

class AAA_fool_method : public Instance
{
public:
    CCC* c;
    Property<uint32> return_value;
    CIMPLE_METHOD(AAA_fool_method)
};

CIMPLE_NAMESPACE_END

#endif /* _AAA_h */