#include "BUG31_C_Provider.h"

using namespace cimple;

CIMPLE_MODULE(BUG31_C_Module);
CIMPLE_PROVIDER(BUG31_C_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(BUG31_C_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_CLASS_DEPENDENCY(BUG31_B);

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/bug31/module.cpp,v 1.2 2007/03/07 20:25:30 mbrasher-public Exp $");
