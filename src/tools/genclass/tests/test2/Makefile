TOP = ../../../../..
include $(TOP)/mak/config.mak

export CIMPLE_MOF_PATH:=$(TOP)/schema

BINARY = genclass_test2

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
	$(BIN_DIR)/genclass CIM_DatabaseAdministrator

tests:
	$(BIN_DIR)/$(BINARY)
