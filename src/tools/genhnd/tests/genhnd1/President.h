/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.0.22
//
//==============================================================================

#ifndef _cimple_President_h
#define _cimple_President_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// President keys:
//     Number

/*[928]*/
class President : public Instance
{
public:
    // President features:
    Property<uint32> Number;
    Property<String> First;
    Property<String> Last;

    CIMPLE_CLASS(President)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_President_h */
