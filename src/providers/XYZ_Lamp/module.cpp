#include "XYZ_Lamp_Provider.h"
#include "XYZ_LampLink_Provider.h"
#include "XYZ_LampIndic_Provider.h"

CIMPLE_MODULE(XYZ_Lamp_Module);
CIMPLE_PROVIDER(XYZ_Lamp_Provider);
CIMPLE_PROVIDER(XYZ_LampLink_Provider);
CIMPLE_PROVIDER(XYZ_LampIndic_Provider);

/* Support for CMPI entry points */
CIMPLE_CMPI_INSTANCE_PROVIDER(XYZ_Lamp_Provider);
CIMPLE_CMPI_ASSOCIATION_PROVIDER(XYZ_LampLink_Provider);
CIMPLE_CMPI_INDICATION_PROVIDER(XYZ_LampIndic_Provider);

/* Support for Pegasus C++ Interface */
// CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/XYZ_Lamp/module.cpp,v 1.2 2007/03/07 20:25:29 mbrasher-public Exp $");
