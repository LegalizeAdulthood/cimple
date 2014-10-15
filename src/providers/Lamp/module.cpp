#include "Lamp_Provider.h"
#include "LampLink_Provider.h"
#include "LampIndic_Provider.h"

CIMPLE_MODULE(Lamp_Module);
CIMPLE_PROVIDER(Lamp_Provider);
CIMPLE_PROVIDER(LampLink_Provider);
CIMPLE_PROVIDER(LampIndic_Provider);

/* Support for CMPI entry points */
CIMPLE_CMPI_INSTANCE_PROVIDER(Lamp_Provider);
CIMPLE_CMPI_ASSOCIATION_PROVIDER(LampLink_Provider);
CIMPLE_CMPI_INDICATION_PROVIDER(LampIndic_Provider);

/* Support for Pegasus C++ Interface */
// CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;
