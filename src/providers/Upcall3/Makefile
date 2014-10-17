TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplupcall3

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
    Upcall3.cpp \
    Upcall3Part.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    Upcall3_Provider.cpp \
    module.cpp

LIBRARIES += cimplepegadap

# NOTE1: add this for pegasus.
INCLUDES += -I$(PEGASUS_ROOT)/src

# NOTE2: add this for pegasus.
DEFINES += -DPEGASUS_PLATFORM_$(CIMPLE_PLATFORM)

# NOTE2: remove this for pegasus.
#FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BINDIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r Upcall3
