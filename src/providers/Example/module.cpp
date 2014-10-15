#include "Example_Provider.h"

using namespace cimple;

CIMPLE_MODULE(Example_Module);
CIMPLE_PROVIDER(Example_Provider);

/* Support for CMPI entry points */
// CIMPLE_CMPI_INSTANCE_PROVIDER(Example_Provider);

/* Support for Pegasus C++ Interface */
CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
