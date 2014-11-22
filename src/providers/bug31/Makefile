TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplebug31

INCLUDES += $(CMPI_INCLUDES)

GENCLASS_SOURCES = \
    BUG31_A.cpp \
    BUG31_B.cpp \
    BUG31_C.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    BUG31_C_Provider.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

BUG31_A.cpp BUG31_B.cpp BUG31_C.cpp repository.cpp: repository.mof
	$(BINDIR)/genclass -r BUG31_A BUG31_B BUG31_C

genclass:
	$(BINDIR)/genclass -r BUG31_A BUG31_B BUG31_C

genprov:
	$(BINDIR)/genprov BUG31_C

genmod:
	$(BINDIR)/genmod BUG31_C BUG31_C
