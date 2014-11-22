TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleea

GENCLASS_SOURCES = \
    EA_Class1.cpp \
    EA_Class2.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    EA_Class2_Provider.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -v -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r EA_Class1 EA_Class2

genprov:
	$(BINDIR)/genprov EA_Class2

genmod:
	$(BINDIR)/genmod EA EA_Class2
