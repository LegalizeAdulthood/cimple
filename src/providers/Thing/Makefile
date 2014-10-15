TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplething

SOURCES = \
    module.cpp \
    repository.cpp \
    Thing.cpp \
    ThingLink.cpp \
    ThingLink_Provider.cpp \
    Thing_Provider.cpp

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
	$(BINDIR)/genclass -r ThingLink

genprov:
	$(BINDIR)/genprov Thing
	$(BINDIR)/genprov ThingLink

genmod:
	$(BINDIR)/genmod Thing Thing ThingLink

live:
	$(CIMCLI) ei Thing --sum -count 10
	$(CIMCLI) ni Thing --sum -count 10
	$(CIMCLI) gi Thing.key=200
	$(CIMCLI) a Thing.key=100 --sum -count 1
	$(CIMCLI) an Thing.key=100 --sum -count 1
	$(CIMCLI) r Thing.key=100 --sum -count 1
	$(CIMCLI) rn Thing.key=100 --sum -count 1
