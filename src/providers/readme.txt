Test and Sample Providers
10 February 2009

This is the common directory for CIMPLE test and example providers.  Each
subdirectory defines a single provider module containing one or more providers.

The providers in these subdirectories have been defined initially for testing
CIMPLE but also serve as examples of CIMPLE provider writing.  Almost all of
them are include in the CIMPLE automatic test suite so that they are
tested for each CIMPLE release at least against Pegasus.

NOTES:

The providers herein typically have handbuild Makefiles since they are
designed to be tests.  However, these Makefiles are general enough that they
serve as good examples of Makefile usage and follow the same form as the
automatically created Makefile except for some extensions for tests, different
forms of module registration, etc.

Generally all of these tests are based on using the CIMPLE tools to generate
the providers but not all of the providers use the latest version of the
tools so there are variations in the generated provider files. 	These tests
also include typicaly the targets for genclass, genprov, genmod and sometimes
genproj to make them easy to regenerate.

Most of the providers also define a client test tool which is either the 
Pegasus client (cimcli) in the provider Makefile or a subdirectory with a
compiled test definition.  The Makefile in this directory defines the set of
providers to be automatically compiled and the set of test clients to be 
compiled and executed as part of the end-end (live:) tests.

Working with these Providers

If you want to work with, use, modify these providers, there are a couple of
helpfull hints:

1. Normally once the live test suite is run, the providers are compiled,
installed, and registered for Pegasus.

2. To modify a provider, simply modify the code and do make insmod to reinstall
the provider.

3. If you modify the class, you must re-register the provider which is normally
a call to the regmod target (make regmod). This may involve actually removing
the previous class and under pegasus the easy way to do this is to use cimcli 
(cimcli dc <className>

4. Most of the providers default to the Pegasus root/cimv2 Namespace with a few
using the root/PG_Interop namespace (in particular for cross-namespace tests.

5. The completely generated output of the CIMPLE genclass, genprov, genmod are
normally included in the CVS repository and CIMPLE distribution so that once
make and make insmod are run either for the whole system and/or the particular
provider, you have a working provider.

Remember that these are both test and demonstration tools so that they will 
contain things that normal providers do not contain and may not always be the
best simple examples.

We are trying to include a readme.txt with each provider to give an overview
of that provider.
