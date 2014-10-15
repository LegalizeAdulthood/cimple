TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = MySpareConfigurationService

INCLUDES += $(CMPI_INCLUDES)

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

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r MySpareConfigurationService MyStorageExtent

genprov:
	$(BINDIR)/genprov MySpareConfigurationService

genmod:
	$(BINDIR)/genmod MySpareConfigurationService MySpareConfigurationService
