//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_Glue_h
#define _cimple_Glue_h

#include <cimple/cimple.h>
#include "Part.h"
#include "Part.h"

CIMPLE_NAMESPACE_BEGIN

class Glue : public Instance
{
public:
    // Glue features:
    CIMPLE_REF(Part,left);
    CIMPLE_REF(Part,right);
    Property<String> message;

    CIMPLE_CLASS(Glue)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Glue_h */
