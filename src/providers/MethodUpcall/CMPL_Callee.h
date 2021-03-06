/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 2.0.0
//
//==============================================================================

#ifndef _cimple_CMPL_Callee_h
#define _cimple_CMPL_Callee_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// CMPL_Callee keys:
//     Key

/*[930]*/
class CMPL_Callee : public Instance
{
public:
    // CMPL_Callee features:
    Property<String> Key;

    CIMPLE_CLASS(CMPL_Callee)
};

/*[1016]*/
class CMPL_Callee_foo1_method : public Instance
{
public:
    Property<uint32> in1;
    Property<String> in2;
    Property<uint32> out1;
    Property<String> out2;
    Property<uint32> return_value;
    CIMPLE_METHOD(CMPL_Callee_foo1_method)
};

/*[1016]*/
class CMPL_Callee_foo2_method : public Instance
{
public:
    Property<uint32> in1;
    Property<String> in2;
    Property<uint32> out1;
    Property<String> out2;
    Property<uint32> return_value;
    CIMPLE_METHOD(CMPL_Callee_foo2_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CMPL_Callee_h */
