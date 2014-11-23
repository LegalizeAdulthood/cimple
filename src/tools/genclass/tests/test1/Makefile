TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass1

GENCLASS_SOURCES = Test1.cpp Test2.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -I ../mof Test1 Test2

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
