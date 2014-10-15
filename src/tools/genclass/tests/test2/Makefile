TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass2

SOURCES = \
    CIM_CommonDatabase.cpp \
    CIM_ConcreteJob.cpp \
    CIM_DatabaseAdministrator.cpp \
    CIM_Dependency.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_OrganizationalEntity.cpp \
    CIM_UserEntity.cpp \
    main.cpp

LIBRARIES = cimple
INCLUDES += -I.

include $(TOP)/mak/rules.mak

genclass:
	$(BINDIR)/genclass CIM_DatabaseAdministrator

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
