TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass5

GENCLASS_SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple

INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

Erp2.cpp:
	$(BINDIR)/genclass Erp2

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_SOURCES:.cpp=.h)

tests:
	$(TARGET)

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass CIM_ComputerSystem
