TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

BINARY = test_person

GENCLASS_SOURCES = Person.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_HEADERS) $(GENCLASS_SOURCES)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass Person

tests:
