TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpletime

GENCLASS_SOURCES = \
    CMPL_Time.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    CMPL_Time_Provider.cpp \
    module.cpp

# Allow building providers for either CMPI or Pegasus C++ provider interface
# Changing Provider interfaces requires reregistering the provider. Default is PEGASUS
ifndef CIMPLE_PROVIDER_TYPE
   CIMPLE_PEGASUS_MODULE = 1
endif

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

## Expand CIMPLE_***_MODULE definitions and CIMPLE_PROVIDER_TYPE
include ../common.mak

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r CMPL_Time

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genprov:
	$(BINDIR)/genprov CMPL_Time

genmod:
	$(BINDIR)/genmod CMPL_Time CMPL_Time

genproj:
	$(BINDIR)/genproj CMPL_Time CMPL_Time
	
manual-test:
	ciminvoke CMPL_Time SetTime Time=20070101120000.123456-360
	ciminvoke CMPL_Time GetTime

