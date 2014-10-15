TOP = ../../..
include $(TOP)/mak/config.mak

MODULE=1

SHARED_LIBRARY = cimplecsdd

SOURCES = \
    CIM_Component.cpp \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_DiskDrive.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_MediaAccessDevice.cpp \
    CIM_SystemComponent.cpp \
    CIM_System.cpp \
    CIM_SystemDevice.cpp \
    ComputerSystem.cpp \
    ComputerSystemDiskDrive.cpp \
    ComputerSystemDiskDrive_Provider.cpp \
    DiskDrive.cpp \
    module.cpp \
    repository.cpp

CIMPLE_PEGASUS_MODULE=1

include ../common.mak

include $(TOP)/mak/rules.mak

regmod:
	$(BINDIR)/regmod -c $(TARGET)

genclass:
	$(BINDIR)/genclass -r ComputerSystemDiskDrive

genprov:
	$(BINDIR)/genprov ComputerSystemDiskDrive

genmod:
	$(BINDIR)/genmod ComputerSystemDiskDrive ComputerSystemDiskDrive
