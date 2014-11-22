TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_model_path

GENCLASS_SOURCES = Part.cpp Glue.cpp repository.cpp
SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Part Glue
