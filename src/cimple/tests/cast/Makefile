TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_cast

GENCLASS_SOURCES = \
    A.cpp \
    B.cpp \
    C.cpp \
    E.cpp \
    D.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass A B C D E
