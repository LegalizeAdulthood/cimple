/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#ifndef _cimple_Test2_h
#define _cimple_Test2_h

#include <cimple/cimple.h>
#include "Test1.h"
#include "Test1.h"

CIMPLE_NAMESPACE_BEGIN

// Test2 keys:

/*[928]*/
class Test2 : public Instance
{
public:
    // Test2 features:
    Property<boolean> ref_field1;
    Property<sint8> ref_field2;
    Property<String> ref_field3;
    Test1* ref1;
    Test1* ref2;

    CIMPLE_CLASS(Test2)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Test2_h */
