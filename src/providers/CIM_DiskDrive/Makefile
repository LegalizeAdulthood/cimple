TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplediskdrive

GENCLASS_SOURCES = \
    CIM_ConcreteJob.cpp \
    CIM_DiskDrive.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_MediaAccessDevice.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES) \
    module.cpp \
    CIM_DiskDrive_Provider.cpp

CIMPLE_CMPI_MODULE=1

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/cimv2 -c $(TARGET)

genclass $(GENCLASS_SOURCES):
	$(BINDIR)/genclass -r CIM_DiskDrive

genprov:
	$(BINDIR)/genprov CIM_DiskDrive

genmod:
	$(BINDIR)/genmod CIM_DiskDrive CIM_DiskDrive
