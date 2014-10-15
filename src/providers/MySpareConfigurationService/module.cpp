#include "MySpareConfigurationService_Provider.h"

using namespace cimple;

CIMPLE_MODULE(MySpareConfigurationService_Provider_Module);
CIMPLE_PROVIDER(MySpareConfigurationService_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(MySpareConfigurationService_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_CLASS_DEPENDENCY(MyStorageExtent)

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MySpareConfigurationService/module.cpp,v 1.2 2007/03/07 20:25:26 mbrasher-public Exp $");

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/MySpareConfigurationService/module.cpp,v 1.2 2007/03/07 20:25:26 mbrasher-public Exp $");
