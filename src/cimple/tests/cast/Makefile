TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_cast

GENCLASS_SOURCES = \
    A.cpp \
    B.cpp \
    C.cpp \
    E.cpp \
    D.cpp

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass A B C D E
