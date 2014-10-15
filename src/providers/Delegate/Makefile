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

#####CIMPLE_CMPI_MODULE=1
## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider.
ifdef CIMPLE_PROVIDER_BUILD_CMPI
    CIMPLE_CMPI_MODULE=1
else
    CIMPLE_PEGASUS_MODULE=1
endif

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
