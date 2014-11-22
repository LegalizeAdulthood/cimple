TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

BINARY = test_person
GENCLASS_SOURCES = Person.cpp
GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)
SOURCES = $(GENCLASS_SOURCES) main.cpp
LIBRARIES = cimple
INCLUDES += -I.
CLEAN += $(GENCLASS_HEADERS) $(GENCLASS_SOURCES)

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_HEADERS) $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -h
	$(BINDIR)/genclass Person

tests:
