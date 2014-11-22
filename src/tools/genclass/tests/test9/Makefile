TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass9

CLASSES = Thing

GENCLASS_SOURCES = $(CLASSES:=.cpp)

GENCLASS_HEADERS = $(CLASSES:=.h)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

INCLUDES += -I.

CLEAN += $(GENCLASS_HEADERS) $(GENCLASS_SOURCES)

include $(TOP)/mak/rules.mak

$(GENCLASS_HEADERS) $(GENCLASS_SOURCES): genclass

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass: repository.mof
	$(BINDIR)/genclass -q -d Thing

tests:
	$(TARGET)
