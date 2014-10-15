TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleDelegate

SOURCES = \
    Delegate.cpp \
    Delegate_Provider.cpp \
    Delegator.cpp \
    Delegator_Provider.cpp \
    repository.cpp \
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

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r Delegate Delegator

genprov:
	$(BINDIR)/genprov Delegate
	$(BINDIR)/genprov Delegator

genmod:
	$(BINDIR)/genmod Delegate Delegate Delegator

live:
	$(CIMCLI) ei Delegate
	$(CIMCLI) ei Delegator
