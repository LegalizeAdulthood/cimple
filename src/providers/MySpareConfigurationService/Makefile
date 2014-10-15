TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = MySpareConfigurationService

INCLUDES += $(CMPI_INCLUDES)

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

SOURCES = \
    CIM_Collection.cpp \
    CIM_ConcreteJob.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_RedundancySet.cpp \
    CIM_Service.cpp \
    CIM_SettingData.cpp \
    CIM_StorageExtent.cpp \
    CIM_StoragePool.cpp \
    CIM_StorageRedundancySet.cpp \
    CIM_StorageSetting.cpp \
    CIM_SystemSpecificCollection.cpp \
    MyStorageExtent.cpp \
    repository.cpp \
    SNIA_SpareConfigurationService.cpp \
    MySpareConfigurationService.cpp \
    MySpareConfigurationService_Provider.cpp \
    module.cpp

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
	genclass -r MySpareConfigurationService MyStorageExtent

genprov:
	genprov -f MySpareConfigurationService
