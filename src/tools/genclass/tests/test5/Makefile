TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(TOP)/schema

BINARY = genclass_test5

SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    main.cpp

LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

Erp2.cpp:
	$(BIN)/genclass Erp2

CLEAN += Erp2.h Erp2.cpp

tests:
	$(TARGET)

genclass:
	$(BIN)/genclass CIM_ComputerSystem
