TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass9

CLASSES = Thing

GENCLASS_SOURCES = $(CLASSES:=.cpp)

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

$(GENCLASS_HEADERS) $(GENCLASS_SOURCES): genclass

genclass: repository.mof
	$(BINDIR)/genclass -q -d Thing

tests:
	$(TARGET)
