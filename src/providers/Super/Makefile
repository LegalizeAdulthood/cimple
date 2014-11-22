TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimpleSuper

GENCLASS_SOURCES = \
	Super.cpp \
	Sub1.cpp \
	Sub2.cpp \
	repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
	Super_Provider.cpp

CIMPLE_PEGASUS_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Super Sub1 Sub2

genprov:
	$(BINDIR)/genprov Super

genmod:
	$(BINDIR)/genmod Super Super

regmod:
	$(BINDIR)/regmod -s -c $(TARGET)

live:
	$(CIMCLI) ei Super
	$(CIMCLI) ni Super --sum -count 2
	$(CIMCLI) ni Sub1 --sum -count 1
	$(CIMCLI) ni Sub2 --sum -count 1
