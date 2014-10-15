//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_LampIndicA_h
#define _cimple_LampIndicA_h

#include <cimple/cimple.h>
#include "LampIndic.h"

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE LampIndicA : public Instance
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

    // LampIndicA features:
    Property<String> messageA;

    CIMPLE_CLASS(LampIndicA)
};

typedef LampIndic_DeliverIndications_method LampIndicA_DeliverIndications_method;

CIMPLE_NAMESPACE_END

#endif /* _cimple_LampIndicA_h */
