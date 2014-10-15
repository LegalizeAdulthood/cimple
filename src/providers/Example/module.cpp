#include "Example_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Example_Module);
CIMPLE_PROVIDER(Example_Provider);

/* Support for CMPI entry points */
// CIMPLE_CMPI_INSTANCE_PROVIDER(Example_Provider);

/* Support for Pegasus C++ Interface */
CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/Example/module.cpp,v 1.9 2007/03/07 20:25:24 mbrasher-public Exp $");
