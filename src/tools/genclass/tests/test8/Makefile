TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = genclass_test8

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

genclass:
	$(BIN_DIR)/genclass -q -d CIM_Card

tests:
	@ $(BINARY_TARGET)
