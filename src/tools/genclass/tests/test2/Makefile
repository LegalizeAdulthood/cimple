TOP = ../../../../..
include $(TOP)/mak/config.mak

BINARY = test_genclass2

GENCLASS_SOURCES = \
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
    CIM_UserEntity.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    main.cpp

LIBRARIES = cimple
INCLUDES += -I.

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass CIM_DatabaseAdministrator

tests:
	$(TARGET)

vg:
	$(VALGRIND) --tool=memcheck --leak-check=full $(TARGET)
