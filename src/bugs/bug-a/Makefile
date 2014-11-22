TOP = ../../..
include $(TOP)/mak/config.mak

INCLUDES += -I../repository

SHARED_LIBRARY = cmplbug

GENCLASS_SOURCES = \
    CIM_Capabilities.cpp \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_RegisteredProfile.cpp \
    CIM_StorageConfigurationCapabilities.cpp \
    CIM_System.cpp \
    ZZZ.cpp \
    ZZZ_ControllerSystem.cpp \
    ZZZ_RegisteredProfile.cpp \
    ZZZ_StorageConfigurationServiceCapabilities.cpp \
    repository.cpp

SOURCES = $(GENCLASS_SOURCES)

LIBRARIES = cimple

LIBRARIES += cimplepegadap

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r ZZZ_StorageConfigurationServiceCapabilities ZZZ_ControllerSystem ZZZ_RegisteredProfile ZZZ
