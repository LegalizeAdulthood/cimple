TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_encoding
GENCLASS_SOURCES = Everything.cpp
SOURCES = $(GENCLASS_SOURCES) main.cpp
LIBRARIES = cimple
DEFINES += -DCIMPLE_LINK_STATIC_LIBCIMPLE

include $(TOP)/mak/rules.mak

tests:
	@ $(BINARY_TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass Everything
