#include "Upcall2_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Upcall2_Module);
CIMPLE_PROVIDER(Upcall2_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(Upcall2_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Upcall2/module.cpp,v 1.2 2007/03/07 20:25:29 mbrasher-public Exp $");
