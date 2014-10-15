TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleHello

SOURCES = \
    repository.cpp \
    Hello.cpp \
    Hello_Provider.cpp \
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
	$(BINDIR)/genclass -r Hello

genprov:
	$(BINDIR)/genprov Hello

genmod:
	$(BINDIR)/genmod Hello Hello

genproj:
	$(BINDIR)/genproj Hello Hello

live:
	cimcli ei -l localhost Hello
	cimcli ni -l localhost Hello

## live manual tests using Pegasus cimcli	
manual-test:
	cimcli ns -l localhost
	cimcli gc -l localhost Hello
	cimcli ei -l localhost Hello
	cimcli ni -l localhost Hello
