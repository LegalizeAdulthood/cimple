TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimple_CIM_StoragePool

INCLUDES += $(CMPI_INCLUDES)

GENCLASS_SOURCES = \
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
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    CIM_StoragePool_Provider.cpp \
    module.cpp

CIMPLE_CMPI_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -r CIM_StoragePool

genprov:
	$(BINDIR)/genprov CIM_StoragePool

genmod:
	$(BINDIR)/genmod CIM_StoragePool CIM_StoragePool
