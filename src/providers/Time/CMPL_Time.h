/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#ifndef _cimple_CMPL_Time_h
#define _cimple_CMPL_Time_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// CMPL_Time keys:

/*[928]*/
class CMPL_Time : public Instance
{
public:
    // CMPL_Time features:

    CIMPLE_CLASS(CMPL_Time)
};

/*[1014]*/
class CMPL_Time_SetTime_method : public Instance
{
public:
    Property<Datetime> Time;
    Property<uint32> return_value;
    CIMPLE_METHOD(CMPL_Time_SetTime_method)
};

/*[1014]*/
class CMPL_Time_GetTime_method : public Instance
{
public:
    Property<Datetime> Time;
    Property<uint32> return_value;
    CIMPLE_METHOD(CMPL_Time_GetTime_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_CMPL_Time_h */
