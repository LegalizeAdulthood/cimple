/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_LampIndic_h
#define _cimple_LampIndic_h

#include <cimple/cimple.h>
#include "CIM_Indication.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE LampIndic : public Instance
{
public:
    // CIM_Indication features:
    Property<String> IndicationIdentifier;
    Property<Array_String> CorrelatedIndications;
    Property<Datetime> IndicationTime;
    Property<uint16> PerceivedSeverity;
    Property<String> OtherSeverity;

    // LampIndic features:
    Property<String> message;

    CIMPLE_CLASS(LampIndic)
};

class CIMPLE_LINKAGE LampIndic_DeliverIndications_method : public Instance
{
public:
    Property<uint32> return_value;
    CIMPLE_METHOD(LampIndic_DeliverIndications_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_LampIndic_h */
