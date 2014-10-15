TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplupcall2

SOURCES = \
    Upcall2_Provider.cpp \
    module.cpp \
    CIM_ManagedElement.cpp \
    CIM_RegisteredProfile.cpp \
    CIM_ElementConformsToProfile.cpp \
    Upcall2Part.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_LogicalElement.cpp \
    CIM_Job.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_System.cpp \
    CIM_ComputerSystem.cpp \
    Upcall2.cpp \
    repository.cpp

LIBRARIES += cimplepegadap cimple

#FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
	genclass -r Upcall2 CIM_ComputerSystem
