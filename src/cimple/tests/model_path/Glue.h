/*NOCHKSRC*/
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

#if (0x00633800 > CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.56) is newer than the version of <cimple/cimple.h> found on the include path. Please place the matching version of <cimple/cimple.h> on the include path."
#endif

#if (0x00633800 < CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.56) is older than the version of <cimple/cimple.h> found on the include path. Please regenerate the sources with the matching version of genclass."
#endif


CIMPLE_NAMESPACE_BEGIN

class Glue : public Instance
{
public:
    // Glue features:
    Part* left;
    Part* right;
    Property<String> message;

    CIMPLE_CLASS(Glue)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Glue_h */
