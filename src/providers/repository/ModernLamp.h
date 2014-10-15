/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_ModernLamp_h
#define _cimple_ModernLamp_h

#include <cimple/cimple.h>
#include "Lamp.h"

#if (0x00633800 > CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.56) is newer than the version of <cimple/cimple.h> found on the include path. Please place the matching version of <cimple/cimple.h> on the include path."
#endif

#if (0x00633800 < CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.56) is older than the version of <cimple/cimple.h> found on the include path. Please regenerate the sources with the matching version of genclass."
#endif


CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE ModernLamp : public Instance
{
public:
    // Lamp features:
    Property<String> model; // KEY
    Property<String> vendor;
    Property<uint32> wattage;
    Property<String> color;

    // ModernLamp features:
    Property<String> artist;

    CIMPLE_CLASS(ModernLamp)
};

typedef Lamp_foo_method ModernLamp_foo_method;

CIMPLE_NAMESPACE_END

#endif /* _cimple_ModernLamp_h */
