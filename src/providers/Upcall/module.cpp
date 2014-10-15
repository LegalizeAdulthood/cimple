#include "Upcall_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Upcall_Module);
CIMPLE_PROVIDER(Upcall_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(Upcall_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Upcall/module.cpp,v 1.3 2007/03/07 20:25:28 mbrasher-public Exp $");
