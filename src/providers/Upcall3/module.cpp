#include "Upcall3_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Upcall3_Module);
CIMPLE_PROVIDER(Upcall3_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(Upcall3_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Upcall3/module.cpp,v 1.2 2007/03/07 20:25:29 mbrasher-public Exp $");
