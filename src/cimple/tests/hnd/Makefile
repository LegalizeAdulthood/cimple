TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = test_handle

SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    repository.cpp \
    test_handle.cpp \
    A.cpp \
    X.cpp \
    Y.cpp \
    E.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	@ $(TARGET)

genclass:
	$(BINDIR)/genclass -l -H -r A E CIM_ComputerSystem CIM_ConcreteJob
