//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_MyClass_h
#define _cimple_MyClass_h

#include <cimple/cimple.h>
#include "YourClass.h"

CIMPLE_NAMESPACE_BEGIN

class MyClass : public Instance
{
public:
    // YourClass features:
    Property<String> str1;
    Property<String> str2;
    Instance* obj1;
    Instance* obj2;

    // MyClass features:
    Property<String> str3;
    Instance* obj3;

    CIMPLE_CLASS(MyClass)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_MyClass_h */
