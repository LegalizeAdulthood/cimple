TOP = ../../..
include $(TOP)/mak/config.mak

TEST_NAMESPACE=root/cimv2

MODULE=1

SHARED_LIBRARY = cimplemethods

GENCLASS_SOURCES = \
    Argument.cpp \
    Methods.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    Methods_Provider.cpp \
    module.cpp \

## Allow building providers for either CMPI or Pegasus C++ provider interface
## Changing Provider interfaces requires reregistering the provider. Default CMPI
##
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_CMPI_MODULE = 1
endif

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Methods

genprov:
	$(BINDIR)/genprov Methods

genmod:
	$(BINDIR)/genmod Methods Methods

##
## Manual tests using cimcli
##

foo3method:
	cimcli im Methods foo3 -l localhost -n $(TEST_NAMESPACE)



