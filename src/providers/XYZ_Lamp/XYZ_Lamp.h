/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#ifndef _cimple_XYZ_Lamp_h
#define _cimple_XYZ_Lamp_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// XYZ_Lamp keys:
//     model

/*[928]*/
class XYZ_Lamp : public Instance
{
public:
    // XYZ_Lamp features:
    Property<String> model;
    Property<String> vendor;
    Property<uint32> wattage;
    Property<String> color;

    CIMPLE_CLASS(XYZ_Lamp)
};

/*[1014]*/
class XYZ_Lamp_foo_method : public Instance
{
public:
    Property<String> arg1;
    Property<String> arg2;
    Property<uint32> return_value;
    CIMPLE_METHOD(XYZ_Lamp_foo_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_XYZ_Lamp_h */
