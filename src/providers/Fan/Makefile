TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplefan

SOURCES = \
    repository.cpp \
    Fan.cpp \
    Fan_Provider.cpp \
    module.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass -r Fan

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genprov:
	$(BINDIR)/genprov Fan

genmod:
	$(BINDIR)/genmod Fan Fan
	
genproj:
	$(BINDIR)/genproj Fan Fan

##============================================================================
##
##  Live Tests - These are tests automatically conducted during regression
##                  Pegasus cimcli used for these live tests.
##                  Does not test results.
##
##============================================================================
live:
	$(CIMCLI) gc fan
	$(CIMCLI) ei fan
	$(CIMCLI) ni fan
	$(CIMCLI) ei fan --sum -count 3
	$(CIMCLI) ni fan --sum -count 3

	$(CIMCLI) gi Fan.DeviceID=\"FAN03\"
	$(CIMCLI) gi Fan.DeviceID=\"FAN02\"
	$(CIMCLI) gi Fan.DeviceID=\"FAN01\"

## The following tests the enumerate, get, and delete functions
## Since it deletes instances, it can be run only once before
## reinitializing the provider which reinstalls the deleted instances.
## This can be done either by waiting for the provider to timeout and
## drop out of memory or by restarting the server. Therefore
## we targeted it as livetests so it will not run as part of
## the automated test Therefore
## we targeted it as livetests so it will not run as part of
## the automated test

##=======================================================================
##
## Live manual tests using Pegasus cimcli
## These tests are a demonstration that the provider works.  They
## do not test the results today, simply assure that there is no exception
## on response
##===========================================================================	
manual-test:
	cimcli ns -l localhost
	cimcli gc $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)
	cimcli ni $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)
	cimcli ei $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)

ei:
	cimcli ei $(TEST_CLASS) -l localhost -n $(TEST_NAMESPACE)

	$(CIMCLI) gi Fan.DeviceID=\"FAN03\"
	$(CIMCLI) gi Fan.DeviceID=\"FAN02\"
	$(CIMCLI) gi Fan.DeviceID=\"FAN01\"

	$(CIMCLI) di Fan.DeviceID=\"FAN03\"
	$(CIMCLI) ni fan --sum -count 2
	$(CIMCLI) di Fan.DeviceID=\"FAN02\"
	$(CIMCLI) ni fan --sum -count 1
	$(CIMCLI) di Fan.DeviceID=\"FAN01\"
	$(CIMCLI) ni fan --sum -count 0
