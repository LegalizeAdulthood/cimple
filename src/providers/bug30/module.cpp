#include "BUG30_X_Provider.h"

using namespace cimple;

CIMPLE_MODULE(BUG30_X_Module);
CIMPLE_PROVIDER(BUG30_X_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(BUG30_X_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_CLASS_DEPENDENCY(BUG30_S)

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/bug30/module.cpp,v 1.3 2007/03/07 20:25:30 mbrasher-public Exp $");
