## 
## Common Functionality for Provider compiling.  The following
## simplifies the definition of provider types for CIMPLE providers and
## provides a way to override the type definition for CIMPLE test providers.
## For CIMPLE Test providers the CIMPLE_PROVIDER_TYPE Makefile
## variable can be used to set providers
##
## The following test allows building providers for either CMPI or 
## Pegasus C++ provider interface.
##
## set CIMPLE_PROVIDER_TEST_TYPE = CMPI | PEGASUS
##
## If CIMPLE_PROVIDER_TYPE not set as shown below, The provider will default 
## to what is set in the Provider Makefile if the following form is used
##   ifndef CIMPLE_PROVIDER_TYPE
##       CIMPLE_PEGASUS_MODULE=1
##   end
##
## NOTE: When changing the CIMPLE_PROVIDER_TEST_TYPE be sure to recompile,
## reregister, and reinstall the providers.

ifdef CIMPLE_PROVIDER_TYPE
    ifeq ($(CIMPLE_PROVIDER_TYPE),PEGASUS)
        CIMPLE_PEGASUS_MODULE = 1
    else
        ifeq ($(CIMPLE_PROVIDER_TYPE),CMPI)
            CIMPLE_CMPI_MODULE = 1
        else
            $(error CIMPLE_PROVIDER_TYPE ($(CIMPLE_PROVIDER_TYPE)) is invalid. \
            It must be set to either PEGASUS or CMPI).
        endif
    endif
endif

##
## If CIMPLE_CMPI_MODULE flag set, build for CMPI
ifdef CIMPLE_CMPI_MODULE
  DEFINES += -DCIMPLE_CMPI_MODULE
  LIBRARIES += cimplecmpiadap cimple
endif

##
## If CIMPLE_PEGASUS_MODULE flag set, build for pegasus
##
ifdef CIMPLE_PEGASUS_MODULE
  DEFINES += -DCIMPLE_PEGASUS_MODULE
  LIBRARIES += cimplepegadap cimplepegutils pegprovider pegclient \
               pegcommon cimple
endif

##  THE FOLLOWING IS OBSOLETE and will be removed.
##  if CIMPLE_PROVIDER_TEST_SELECT flag set, let the flag
## CIMPLE_PROVIDER_BUILD_CMPI decide.  If this env flag is set
## we build as CMPI. Else we build as C++
## This is primarily a test tool so we can build all providers both ways
## with a single top level flag.
##
#ifdef CIMPLE_PROVIDER_TEST_SELECT
#    ifdef CIMPLE_PROVIDER_BUILD_CMPI
#        CIMPLE_CMPI_MODULE=1
#    else
#        CIMPLE_PEGASUS_MODULE=1
#    endif
#endif
