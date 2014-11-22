TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplearrays

GENCLASS_SOURCES = \
    Arrays.cpp \
    repository.cpp
GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)
CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    Arrays_Provider.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

regmod:
	$(BINDIR)/regmod -n root/cimv2 -c $(TARGET)

$(GENCLASS_SOURCES) $(GENCLASS_HEADERS): repository.mof
	$(BINDIR)/genclass -r Arrays

genclass:
	$(BINDIR)/genclass -r Arrays

genprov:
	$(BINDIR)/genprov Arrays

genmod:
	$(BINDIR)/genmod Arrays Arrays

live:
	$(CIMCLI) ni Arrays --sum -count 1
	$(CIMCLI) ei Arrays	--sum -count 1
manual-test:
	$(CIMCLI) ni Arrays
	$(CIMCLI) ei Arrays
