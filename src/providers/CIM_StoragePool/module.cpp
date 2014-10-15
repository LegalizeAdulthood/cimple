#include "CIM_StoragePool_Provider.h"

using namespace cimple;

CIMPLE_MODULE(CIM_StoragePool_Provider_Module);
CIMPLE_PROVIDER(CIM_StoragePool_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(CIM_StoragePool_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/CIM_StoragePool/module.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
