TOP = ../../..
include $(TOP)/mak/config.mak

SHARED_LIBRARY = cmplrep

CLASSES = \
    Persistent \
    Fan  \
    Arrays \
    MyIndication \
    DerivedIndication \
    Example \
    LinuxComputerSystem \
    Person \
    Salesman \
    Link \
    Person2 \
    Link2 \
    Methods \
    UnixUser \
    User \
    MyEmbeddedClass \
    DiskDrive \
    ComputerSystem \
    ComputerSystemDiskDrive \
    Thing \
    ThingLink \
    Lamp \
    ModernLamp \
    LampLink \
    LampIndic \
    LampIndicA \
    LampIndicB \
    LampIndicC \
    XYZ_Lamp \
    XYZ_LampLink \
    XYZ_LampIndic

GENCLASS_SOURCES = \
    Arg.cpp \
    Arrays.cpp \
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
    CIM_System.cpp \
    CIM_SystemComponent.cpp \
    CIM_SystemDevice.cpp \
    ComputerSystem.cpp \
    ComputerSystemDiskDrive.cpp \
    DerivedIndication.cpp \
    DiskDrive.cpp \
    Example.cpp \
    Fan.cpp \
    House.cpp \
    Lamp.cpp \
    LampIndic.cpp \
    LampIndicA.cpp \
    LampIndicB.cpp \
    LampIndicC.cpp \
    LampLink.cpp \
    Link.cpp \
    Link2.cpp \
    LinuxComputerSystem.cpp \
    Methods.cpp \
    ModernLamp.cpp \
    MyEmbeddedClass.cpp \
    MyIndication.cpp \
    Persistent.cpp \
    Person.cpp \
    Person2.cpp \
    Salesman.cpp \
    Thing.cpp \
    ThingLink.cpp \
    UnixUser.cpp \
    User.cpp \
    XYZ_Lamp.cpp \
    XYZ_LampIndic.cpp \
    XYZ_LampLink.cpp \
    repository.cpp

GENCLASS_HEADERS = $(GENCLASS_SOURCES:.cpp=.h)

CLEAN += $(GENCLASS_SOURCES) $(GENCLASS_HEADERS)

SOURCES = \
    $(GENCLASS_SOURCES)

LIBRARIES = cimple

FLAGS += $(SIZE_OPTIMIZATION_FLAGS)

DEFINES += -DCIMPLE_INTERNAL

export CIMPLE_MOF_PATH=$(TOP)/schema/cim214

include $(TOP)/mak/rules.mak

repository.mof: \
    Arrays.mof \
    ComputerSystemDiskDrive.mof \
    DerivedIndication.mof \
    Example.mof \
    Fan.mof \
    Lamp.mof \
    LinuxComputerSystem.mof \
    Methods.mof \
    MyEmbeddedClass.mof \
    Persistent.mof \
    Person.mof \
    Person2.mof \
    Thing.mof \
    UnixUser.mof \
    User.mof \
    XYZ_Lamp.mof

genclass $(GENCLASS_SOURCES): repository.mof
	$(BINDIR)/genclass -l -r $(CLASSES)

tests:
	@ $(BINDIR)/dlopen $(SHARED_LIBRARY_TARGET)
