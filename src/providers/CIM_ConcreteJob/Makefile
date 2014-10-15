TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmpl_CIM_ConcreteJob

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

SOURCES = \
    CIM_ConcreteJob.cpp \
    CIM_ConcreteJob_Provider.cpp \
    CIM_Job.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    module.cpp \
    repository.cpp

LIBRARIES = cimple

#BUILD_CMPI_PROVIDER=1
ifdef BUILD_CMPI_PROVIDER
  LIBRARIES += cimplecmpiadap
  DEFINES += -DBUILD_CMPI_PROVIDER
else
  LIBRARIES += cimplepegadap
endif

include $(TOP)/mak/rules.mak

reg:
	regmod -c $(SHARED_LIBRARY_TARGET)

tests:

genclass:
	genclass -r CIM_ConcreteJob

genprov:
	genprov -f CIM_ConcreteJob

