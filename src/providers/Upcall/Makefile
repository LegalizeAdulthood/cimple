TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplupcall


SOURCES = \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_System.cpp \
    module.cpp \
    repository.cpp \
    Upcall.cpp \
    Upcall_Provider.cpp

# Uncommment this to build a CMPI provider.
#BUILD_CMPI_PROVIDER=1

LIBRARIES += cimple

ifdef BUILD_CMPI_PROVIDER
  LIBRARIES += cimplecmpiadap
  DEFINES += -DBUILD_CMPI_PROVIDER
else
  LIBRARIES += cimplepegadap
endif

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

include $(TOP)/mak/rules.mak

tests:

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:
	@ $(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

genclass:
	genclass -r Upcall CIM_ComputerSystem
