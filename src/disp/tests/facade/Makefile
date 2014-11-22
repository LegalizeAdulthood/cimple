TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_facade

GENCLASS_SOURCES = Base.cpp Thing.cpp Assoc.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimpledisp cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass Thing Assoc Base

tests:
	@ $(BINARY_TARGET)
