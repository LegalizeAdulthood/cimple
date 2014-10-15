TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genhnd1

SOURCES = \
    CIM_Collection.cpp \
    CIM_CollectionOfMSEs.cpp \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_Setting.cpp \
    CIM_System.cpp \
    CIM_SystemSetting.cpp \
    Assoc.cpp \
    ConcreteAssoc.cpp \
    main.cpp

LIBRARIES = cimple

include $(TOP)/mak/rules.mak

tests:
	$(TARGET)

gen:
	$(BINDIR)/genclass CIM_ComputerSystem CIM_SystemSetting Assoc ConcreteAssoc
	$(BINDIR)/genhnd CIM_ComputerSystem CIM_SystemSetting Assoc ConcreteAssoc
