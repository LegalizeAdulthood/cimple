/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 2.0.7
//
//==============================================================================

#ifndef _cimple_Place_h
#define _cimple_Place_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// Place keys:
//     SSN

/*[930]*/
class Place : public Instance
{
public:
    // Place features:
    Property<String> SSN;
    Property<String> FirstName;
    Property<String> LastName;

    CIMPLE_CLASS(Place)
};

/*[1016]*/
class Place_foo_method : public Instance
{
public:
    Property<String> arg;
    Property<uint32> return_value;
    CIMPLE_METHOD(Place_foo_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Place_h */
