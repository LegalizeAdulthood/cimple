TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass3

GENCLASS_SOURCES = Erp.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -I ../mof Erp

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
