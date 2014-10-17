TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplupcall2

GENCLASS_SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_ElementConformsToProfile.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_RegisteredProfile.cpp \
    CIM_System.cpp \
    Upcall2.cpp \
    Upcall2Part.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    Upcall2_Provider.cpp \
    module.cpp

LIBRARIES += cimplepegadap cimple

#FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Upcall2 CIM_ComputerSystem
