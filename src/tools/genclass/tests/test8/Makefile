TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass8

GENCLASS_SOURCES = \
    CIM_Card.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_PhysicalConnector.cpp \
    CIM_PhysicalElement.cpp \
    CIM_PhysicalPackage.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

$(GENCLASS_HEADERS) $(GENCLASS_SOURCES): genclass

genclass:
	$(BINDIR)/genclass -q -d CIM_Card
