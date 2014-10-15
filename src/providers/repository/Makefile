TOP = ../../..
include $(TOP)/mak/config.mak

SH_LIBRARY = cmplrep

CLASSES = \
    Fan  \
    MyIndication \
    DerivedIndication \
    Example \
    LinuxComputerSystem \
    Person \
    Link \
    Methods \
    UnixUser \
    MyEmbeddedClass \
    DiskDrive \
    ComputerSystem \
    ComputerSystemDiskDrive \
    Thing \
    ThingLink

SOURCES = \
    DiskDrive.cpp \
    ComputerSystem.cpp \
    ComputerSystemDiskDrive.cpp \
    Arg.cpp \
    CIM_Component.cpp \
    CIM_ComputerSystem.cpp \
    CIM_ConcreteJob.cpp \
    CIM_DiskDrive.cpp \
    CIM_EnabledLogicalElement.cpp \
    CIM_Indication.cpp \
    CIM_Job.cpp \
    CIM_LogicalDevice.cpp \
    CIM_LogicalElement.cpp \
    CIM_ManagedElement.cpp \
    CIM_ManagedSystemElement.cpp \
    CIM_MediaAccessDevice.cpp \
    CIM_SystemComponent.cpp \
    CIM_System.cpp \
    CIM_SystemDevice.cpp \
    DerivedIndication.cpp \
    Example.cpp \
    Fan.cpp \
    House.cpp \
    Link.cpp \
    LinuxComputerSystem.cpp \
    Methods.cpp \
    MyEmbeddedClass.cpp \
    MyIndication.cpp \
    Person.cpp \
    repository.cpp \
    UnixUser.cpp \
    Thing.cpp \
    ThingLink.cpp

LIBRARIES = cimple

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLE_INTERNAL

include $(TOP)/mak/rules.mak

genclass:
	genclass -l -r $(CLASSES)

tests:
	@ $(BIN)/dlopen $(TARGET)