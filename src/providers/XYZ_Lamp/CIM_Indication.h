//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _CIM_Indication_h
#define _CIM_Indication_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

class CIM_Indication : public Instance
{
public:
    // CIM_Indication features:
    Property<String> IndicationIdentifier;
    Property<Array_String> CorrelatedIndications;
    Property<Datetime> IndicationTime;
    Property<uint16> PerceivedSeverity;
    Property<String> OtherSeverity;

    CIMPLE_CLASS(CIM_Indication)
};

CIMPLE_NAMESPACE_END

#endif /* _CIM_Indication_h */
