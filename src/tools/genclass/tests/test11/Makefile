TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test11

GENCLASS_SOURCES = \
    repository.cpp \
    A.cpp \
    B.cpp \
    C.cpp \
    X.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp \

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r X

tests:
	$(TARGET)
