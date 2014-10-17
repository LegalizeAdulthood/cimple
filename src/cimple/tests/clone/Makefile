TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_clone

GENCLASS_SOURCES = MyClass.cpp repository.cpp
SOURCES = $(GENCLASS_SOURCES) test_clone.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r MyClass
