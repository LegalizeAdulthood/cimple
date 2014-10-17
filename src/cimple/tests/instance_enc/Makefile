TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_encoding_enc
GENCLASS_SOURCES = Everything.cpp
SOURCES = $(GENCLASS_SOURCES) main.cpp
LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass Everything

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
