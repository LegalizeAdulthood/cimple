TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass4

GENCLASS_SOURCES = Erp2.cpp

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -I ../mof Erp2
