#include "CIM_ConcreteJob_Provider.h"

using namespace cimple;

CIMPLE_MODULE(CIM_ConcreteJob_Provider_Module);
CIMPLE_PROVIDER(CIM_ConcreteJob_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(CIM_ConcreteJob_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/CIM_ConcreteJob/module.cpp,v 1.1 2007/03/13 21:42:10 mbrasher-public Exp $");
