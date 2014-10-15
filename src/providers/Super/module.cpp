#include "Super_Provider.h"

CIMPLE_MODULE(Super_Module);
CIMPLE_PROVIDER(Super_Provider);

#ifdef USE_CMPI
    CIMPLE_CMPI_INSTANCE_PROVIDER(Super_Provider);
#else
    CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Super/module.cpp,v 1.4 2007/03/07 20:25:28 mbrasher-public Exp $");
