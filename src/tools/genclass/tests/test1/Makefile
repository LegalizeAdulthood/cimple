TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass1

GENCLASS_SOURCES = Test1.cpp Test2.cpp

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -I ../mof Test1 Test2

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
