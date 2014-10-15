//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _Methods_h
#define _Methods_h

#include <cimple/cimple.h>
#include "Arg.h"
#include "Arg.h"

CIMPLE_NAMESPACE_BEGIN

class Methods : public Instance
{
public:
    // Methods features:
    Property<uint32> key;

    CIMPLE_CLASS(Methods)
};

class Methods_foo_method : public Instance
{
public:
    Property<uint32> arg1;
    Property<String> arg2;
    Property<boolean> arg3;
    Property<uint32> arg4;
    Property<String> arg5;
    Property<boolean> arg6;
    Property<String> return_value;
    CIMPLE_METHOD(Methods_foo_method)
};

class Methods_foo2_method : public Instance
{
public:
    Arg* arg1;
    Arg* arg2;
    Property<String> return_value;
    CIMPLE_METHOD(Methods_foo2_method)
};

class Methods_foo3_method : public Instance
{
public:
    Property<String> return_value;
    CIMPLE_METHOD(Methods_foo3_method)
};

CIMPLE_NAMESPACE_END

#endif /* _Methods_h */
