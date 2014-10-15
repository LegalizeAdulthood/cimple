#include "Fan_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Fan_Module);
CIMPLE_PROVIDER(Fan_Provider);

/* Support for CMPI entry points */
// CIMPLE_CMPI_INSTANCE_PROVIDER(Fan_Provider);

/* Support for Pegasus C++ Interface */
CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Fan/module.cpp,v 1.5 2007/03/07 20:25:24 mbrasher-public Exp $");
