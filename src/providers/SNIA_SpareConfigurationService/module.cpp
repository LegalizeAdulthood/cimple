#include "SNIA_SpareConfigurationService_Provider.h"

using namespace cimple;

CIMPLE_MODULE(SNIA_SpareConfigurationService_Provider_Module);
CIMPLE_PROVIDER(SNIA_SpareConfigurationService_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(SNIA_SpareConfigurationService_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_CLASS_DEPENDENCY(MyStorageExtent)

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/SNIA_SpareConfigurationService/module.cpp,v 1.2 2007/03/07 20:25:28 mbrasher-public Exp $");
