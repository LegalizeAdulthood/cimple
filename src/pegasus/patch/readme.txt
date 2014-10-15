
This directory contains a patch which must be manually applied to:

    src/Pegasus/ProviderManager2/BasicProviderManagerRouter.cpp

It should immediately follow this block of code:

    #if defined(PEGASUS_ENABLE_JMPI_PROVIDER_MANAGER)
	.
	.
	.
	.
    #endif

And immediately before this line:

    // END TEMP SECTION

