TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_facade
GENCLASS_SOURCES = Base.cpp Thing.cpp Assoc.cpp
SOURCES = $(GENCLASS_SOURCES) main.cpp
LIBRARIES = cimpledisp cimple

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass Thing Assoc Base

tests:
	@ $(BINARY_TARGET)
