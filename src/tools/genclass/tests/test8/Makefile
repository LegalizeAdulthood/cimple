TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass8

SOURCES = \
    main.cpp \
    CIM_Card.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_PhysicalConnector.cpp \
    CIM_PhysicalElement.cpp \
    CIM_PhysicalPackage.cpp \

LIBRARIES = cimple

INCLUDES += -I.

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

genclass:
	$(BINDIR)/genclass -q -d CIM_Card
