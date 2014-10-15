#include "Methods_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Methods_Module);
CIMPLE_PROVIDER(Methods_Provider);

/* Support for CMPI entry points */
// CIMPLE_CMPI_INSTANCE_PROVIDER(Methods_Provider);

/* Support for Pegasus C++ Interface */
CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Methods/module.cpp,v 1.5 2007/03/07 20:25:25 mbrasher-public Exp $");
