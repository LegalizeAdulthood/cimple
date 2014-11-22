TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_serialize

GENCLASS_SOURCES = \
    All_Embedded.cpp \
    All_Properties.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
	$(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass All_Properties All_Embedded

