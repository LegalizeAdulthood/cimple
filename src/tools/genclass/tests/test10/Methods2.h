/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.3
//
//==============================================================================

#ifndef _cimple_Methods2_h
#define _cimple_Methods2_h

#include <cimple/cimple.h>
#include "Methods.h"

CIMPLE_NAMESPACE_BEGIN

// Methods2 keys:
//     key

class Methods2 : public Instance
{
public:
    // Methods features:
    Property<uint32> key;

    // Methods2 features:

    CIMPLE_CLASS(Methods2)
};

typedef Methods_foo_method Methods2_foo_method;

typedef Methods_foo2_method Methods2_foo2_method;

typedef Methods_foo3_method Methods2_foo3_method;

typedef Methods_foo4_method Methods2_foo4_method;

typedef Methods_foo5_method Methods2_foo5_method;

class Methods2_junk_method : public Instance
{
public:
    Property<uint32> x;
    Property<uint32> y;
    Property<uint32> return_value;
    CIMPLE_METHOD(Methods2_junk_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Methods2_h */
