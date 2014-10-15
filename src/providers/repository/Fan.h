//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _Fan_h
#define _Fan_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE Fan : public Instance
{
public:
    // Fan features:
    Property<String> DeviceID;
    Property<uint64> Speed;
    Property<uint64> DesiredSpeed;

    CIMPLE_CLASS(Fan)
};

class CIMPLE_LINKAGE Fan_SetSpeed_method : public Instance
{
public:
    Property<uint64> DesiredSpeed;
    Property<uint32> return_value;
    CIMPLE_METHOD(Fan_SetSpeed_method)
};

CIMPLE_NAMESPACE_END

#endif /* _Fan_h */
