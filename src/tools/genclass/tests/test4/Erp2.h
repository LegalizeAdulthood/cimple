/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_Erp2_h
#define _cimple_Erp2_h

#include <cimple/cimple.h>

#if (0x00633800 > CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.56) is newer than the version of <cimple/cimple.h> found on the include path. Please place the matching version of <cimple/cimple.h> on the include path."
#endif

#if (0x00633800 < CIMPLE_VERSION)
# error "The version of genclass used to generate this file (0.99.56) is older than the version of <cimple/cimple.h> found on the include path. Please regenerate the sources with the matching version of genclass."
#endif


CIMPLE_NAMESPACE_BEGIN

class Erp2 : public Instance
{
public:
    // Erp2 features:
    Property<String> w; // KEY
    Property<uint32> x;
    Property<Array_String> y;
    Property<Array_String> z;

    CIMPLE_CLASS(Erp2)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Erp2_h */
