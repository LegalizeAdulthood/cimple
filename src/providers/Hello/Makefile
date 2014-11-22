TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleHello

GENCLASS_SOURCES = \
    Hello.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    Hello_Provider.cpp \
    module.cpp

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default Pegasus
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
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
