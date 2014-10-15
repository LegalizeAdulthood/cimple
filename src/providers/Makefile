TOP = ../..
include $(TOP)/mak/config.mak

DIRS = \
    Arrays \
    bug31 \
    CIM_ConcreteJob \
    CIM_DiskDrive \
    ComputerSystemDiskDrive \
    Cross \
    DerivedIndication \
    Example \
    Fan \
    Lamp \
    LinuxComputerSystem \
    Methods \
    MyIndication \
    Person \
    RefArray \
    Super \
    Thing \
    Upcall \
    XYZ_Lamp \
    Fan/set_speed \
    Methods/foo \
    Methods/foo2 \
    bug31/meth \
    RefArray/SendRefArray \
    CIM_ConcreteJob/meth \
    Delegate \
    Employee \
    Time \
    Time/InvokeTime \

ifeq ($(ENABLE_EMBEDDED_INSTANCES_OPT),1)
    DIRS += Embedded Embedded/TestEmbedded All All/TestAll
endif

ifdef CIMPLE_UNIX
  DIRS += UnixUser
endif

include $(TOP)/mak/dir.mak
include ../pegasus/check-pegasus.mak
include ../cmpi/check-cmpi.mak
