TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass6

CLASSES = AAA2 AAA BBB CCC DDD

GENCLASS_SOURCES = $(CLASSES:=.cpp)

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = $(GENCLASS_SOURCES) main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

$(GENCLASS_SOURCES) $(GENCLASS_HEADERS): genclass

genclass: repository.mof
	$(BINDIR)/genclass BBB CCC DDD AAA AAA2
