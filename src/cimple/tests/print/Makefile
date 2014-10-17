TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_print

GENCLASS_SOURCES = SomeClass.cpp OtherClass.cpp

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass SomeClass OtherClass

tests:
	$(BINDIR)/test_print

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
