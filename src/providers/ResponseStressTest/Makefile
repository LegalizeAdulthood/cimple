TOP = ../../..
include $(TOP)/mak/config.mak

## Defines this as a provider module to the CIMPLE make environment
## The target insmod can be used to install the provider shared library
MODULE=1

SHARED_LIBRARY = cimpleResponseStressTest

## Define list of classes we want to gen and corresponding Providers
## providers we want to build into module.  Note that here they are
## the same.
CLASSES = CMPL_ResponseStressTest
PROVIDER_MODULE = CMPL_ResponseStressTest

SOURCES = \
    repository.cpp \
    CMPL_ResponseStressTest.cpp \
    CMPL_ResponseStressTest_Provider.cpp \
    module.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider.
## Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

###############################################################################
##
## CIMPLE tool targets to build the classes, providers, and module
##
###############################################################################

genclass:
	$(BINDIR)/genclass -r $(CLASSES)

genprov:
	$(BINDIR)/genprov $(CLASSES)	

genmod:
	$(BINDIR)/genmod $(PROVIDER_MODULE)  $(CLASSES)

## As an alternate to getclass, genprov, and genproj you can use the
## following which does all three commands.
genproj:
	$(BINDIR)/genmod $(PROVIDER_MODULE) $(CLASSES)

regmod:
	$(BINDIR)/regmod -c $(TARGET)

unregister:
	$(BINDIR)/regmod -u -c $(TARGET)
