TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplediskdrive

SOURCES = \
    CIM_ConcreteJob.cpp \
    CIM_DiskDrive.cpp \
    CIM_DiskDrive_Provider.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_MediaAccessDevice.cpp \
    module.cpp \
    repository.cpp

CIMPLE_CMPI_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -n root/cimv2 -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r CIM_DiskDrive

genprov:
	$(BINDIR)/genprov CIM_DiskDrive

genmod:
	$(BINDIR)/genmod CIM_DiskDrive CIM_DiskDrive
