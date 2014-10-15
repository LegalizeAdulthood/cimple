/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 2.1.0
//
//==============================================================================

#ifndef _cimple_Methods_h
#define _cimple_Methods_h

#include <cimple/cimple.h>
#include "Argument.h"
#include "Argument.h"

CIMPLE_NAMESPACE_BEGIN

// Methods keys:
//     key

/*[1204]*/
class Methods : public Instance
{
public:
    // Methods features:
    Property<uint32> key;

    CIMPLE_CLASS(Methods)
};

/*[1290]*/
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

/*[1290]*/
class Methods_foo2_method : public Instance
{
public:
    Argument* arg1;
    Argument* arg2;
    Property<String> return_value;
    CIMPLE_METHOD(Methods_foo2_method)
};

/*[1290]*/
class Methods_foo3_method : public Instance
{
public:
    Property<String> return_value;
    CIMPLE_METHOD(Methods_foo3_method)
};

/*[1290]*/
class Methods_foo4_method : public Instance
{
public:
    Property<Array_String> arr1;
    Property<Array_String> arr2;
    Property<uint32> return_value;
    CIMPLE_METHOD(Methods_foo4_method)
};

/*[1290]*/
class Methods_foo5_method : public Instance
{
public:
    Property<uint32> in_arg;
    Property<uint32> in_out_arg;
    Property<uint32> out_arg;
    Property<uint32> return_value;
    CIMPLE_METHOD(Methods_foo5_method)
};

/*[1290]*/
class Methods_junk_method : public Instance
{
public:
    Property<uint32> x;
    Property<uint32> y;
    Property<uint32> return_value;
    CIMPLE_METHOD(Methods_junk_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Methods_h */
