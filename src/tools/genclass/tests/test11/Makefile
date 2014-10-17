TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test11

GENCLASS_SOURCES = \
    repository.cpp \
    A.cpp \
    B.cpp \
    C.cpp \
    X.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp \

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r X

tests:
	$(TARGET)
