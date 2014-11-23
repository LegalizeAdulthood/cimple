TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_print

GENCLASS_SOURCES = SomeClass.cpp OtherClass.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass SomeClass OtherClass

tests:
	$(BINDIR)/test_print

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
