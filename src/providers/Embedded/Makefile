TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleemb

GENCLASS_SOURCES = \
    CMPL_Embedded.cpp \
    CMPL_Embedded1.cpp \
    CMPL_Embedded2.cpp \
    CMPL_Embedded3.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    CMPL_Embedded_Provider.cpp \
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

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r CMPL_Embedded

genprov:
	$(BINDIR)/genprov CMPL_Embedded

genmod:
	$(BINDIR)/genmod CMPL_Embedded CMPL_Embedded

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genproj:
	$(BINDIR)/genproj CMPL_Embedded CMPL_Embedded
