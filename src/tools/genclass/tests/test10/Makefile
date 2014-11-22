TOP = ../../../../..
include $(TOP)/mak/config.mak

LIBRARY = junk

GENCLASS_SOURCES = \
    Argument.cpp \
    Methods2.cpp \
    Methods.cpp \
    repository.cpp

SOURCES = $(GENCLASS_SOURCES)

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -r Methods Methods2
