TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = SNIA_SpareConfigurationService

INCLUDES += $(CMPI_INCLUDES)

GENCLASS_SOURCES = \
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
    SNIA_SpareConfigurationService.cpp \
    repository.cpp

SOURCES = \
    $(GENCLASS_SOURCES) \
    SNIA_SpareConfigurationService_Provider.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

repository.mof: SNIA_SparingSubprofile.mof
genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -r SNIA_SpareConfigurationService MyStorageExtent

genprov:
	$(BINDIR)/genprov SNIA_SpareConfigurationService

genmod:
	$(BINDIR)/genmod SNIA_SpareConfigurationService SNIA_SpareConfigurationService
