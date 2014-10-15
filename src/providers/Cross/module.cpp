#include "CMPL_Left_Provider.h"
#include "CMPL_Right_Provider.h"
#include "CMPL_Cross_Provider.h"

CIMPLE_MODULE(CMPL_Cross_Module);
CIMPLE_PROVIDER(CMPL_Cross_Provider);
CIMPLE_PROVIDER(CMPL_Left_Provider);
CIMPLE_PROVIDER(CMPL_Right_Provider);

#ifdef BUILD_CMPI_PROVIDER
  CIMPLE_CMPI_INSTANCE_PROVIDER(CMPL_Left_Provider);
  CIMPLE_CMPI_INSTANCE_PROVIDER(CMPL_Right_Provider);
  CIMPLE_CMPI_ASSOCIATION_PROVIDER(CMPL_Cross_Provider);
#else
  CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
#endif

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Cross/module.cpp,v 1.2 2007/03/07 20:25:24 mbrasher-public Exp $");
