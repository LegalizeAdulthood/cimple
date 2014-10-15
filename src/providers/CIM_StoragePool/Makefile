TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmpl_CIM_StoragePool

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

SOURCES = \
    repository.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_SettingData.cpp \
    CIM_StorageExtent.cpp \
    CIM_StoragePool.cpp \
    CIM_StorageSetting.cpp \
    module.cpp \
    CIM_StoragePool_Provider.cpp

LIBRARIES = cimple

BUILD_CMPI_PROVIDER=1
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
	genclass -r CIM_StoragePool

genprov:
	genprov -f BUG30_X
