TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplederivedindic

GENCLASS_SOURCES = \
    CIM_Indication.cpp \
    DerivedIndication.cpp \
    MyIndication.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    DerivedIndication_Provider.cpp \
    module.cpp

CIMPLE_PEGASUS_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r DerivedIndication

genprov:
	$(BINDIR)/genprov DerivedIndication

genmod:
	$(BINDIR)/genmod DerivedIndication DerivedIndication
