TOP = ../../../../..
include $(TOP)/mak/config.mak

LIBRARY = junk

GENCLASS_SOURCES = \
    Argument.cpp \
    Methods2.cpp \
    Methods.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES)

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -r Methods Methods2
