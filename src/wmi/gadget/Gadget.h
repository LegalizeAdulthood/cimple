/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.2.5
//
//==============================================================================

#ifndef _cimple_Gadget_h
#define _cimple_Gadget_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// Gadget keys:
//     key

/*[930]*/
class Gadget : public Instance
{
public:
    // Gadget features:
    Property<String> key;
    Property<boolean> b;
    Property<uint8> u8;
    Property<sint8> s8;
    Property<uint8> u16;
    Property<sint8> s16;
    Property<uint8> u32;
    Property<sint8> s32;
    Property<uint8> u64;
    Property<sint8> s64;
    Property<real32> r32;
    Property<real64> r64;
    Property<Datetime> dt;
    Property<Array_boolean> ba;
    Property<Array_uint8> u8a;
    Property<Array_sint8> s8a;
    Property<Array_uint16> u16a;
    Property<Array_sint16> s16a;
    Property<Array_uint32> u32a;
    Property<Array_sint32> s32a;
    Property<Array_uint64> u64a;
    Property<Array_sint64> s64a;
    Property<Array_real32> r32a;
    Property<Array_real64> r64a;
    Property<Array_String> sa;
    Property<Array_Datetime> dta;

    CIMPLE_CLASS(Gadget)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Gadget_h */
