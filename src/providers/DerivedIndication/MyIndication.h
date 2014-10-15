/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT; THIS FILE WAS AUTOMATICALLY GENERATED BY GENCLASS 1.1.2
//
//==============================================================================

#ifndef _cimple_MyIndication_h
#define _cimple_MyIndication_h

#include <cimple/cimple.h>
#include "CIM_Indication.h"

CIMPLE_NAMESPACE_BEGIN

// MyIndication keys:

/*[928]*/
class MyIndication : public Instance
{
public:
    // CIM_Indication features:
    Property<String> IndicationIdentifier;
    Property<Array_String> CorrelatedIndications;
    Property<Datetime> IndicationTime;
    Property<uint16> PerceivedSeverity;
    Property<String> OtherSeverity;

    // MyIndication features:
    Instance* object;

    CIMPLE_CLASS(MyIndication)
};

/*[1014]*/
class MyIndication_DeliverIndications_method : public Instance
{
public:
    Property<uint32> return_value;
    CIMPLE_METHOD(MyIndication_DeliverIndications_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_MyIndication_h */
