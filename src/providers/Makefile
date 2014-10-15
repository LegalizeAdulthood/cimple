TOP = ../..
include $(TOP)/mak/config.mak

DIRS = \
    repository \
    Person \
    LinuxComputerSystem \
    Example \
    Fan \
    Methods \
    MyIndication \
    DerivedIndication \
    ComputerSystemDiskDrive \
    Lamp \
    XYZ_Lamp \
    Thing \
    Salesman \
    Arrays \
    CIM_DiskDrive \
    Super \
    President

ifdef CIMPLE_UNIX
    DIRS += UnixUser
endif

include $(TOP)/mak/dir.mak

ifdef PEGASUS_HOME

DIRS += \
    Person/create_person \
    Person/modify_person \
    Fan/set_speed \
    Methods/foo \
    Methods/foo2

reg:
	$(MAKE) -C $(TOP)/src/providers/Person reg
	$(MAKE) -C $(TOP)/src/providers/Fan reg
	$(MAKE) -C $(TOP)/src/providers/Methods reg
	$(MAKE) -C $(TOP)/src/providers/ComputerSystemDiskDrive reg
	$(MAKE) -C $(TOP)/src/providers/Thing reg
	$(MAKE) -C $(TOP)/src/providers/Lamp reg
	$(MAKE) -C $(TOP)/src/providers/Super reg

live-tests:
	$(CIMCLI) gi Person.ssn=1
	$(CIMCLI) ni Person
	$(CIMCLI) ni Link
	$(CIMCLI) ni Link
	$(CIMCLI) ni Fan
	$(CIMCLI) ei Person
	$(CIMCLI) ei Link
	$(CIMCLI) ei Link
	$(CIMCLI) ei Fan
	$(CIMCLI) an Person
	$(CIMCLI) an Person.ssn=1
	$(CIMCLI) an Person.ssn=2
	$(CIMCLI) an Person.ssn=3
	$(CIMCLI) an Person.ssn=4
	$(CIMCLI) an Person.ssn=5
	$(CIMCLI) a Person.ssn=1
	$(CIMCLI) a Person.ssn=2
	$(CIMCLI) a Person.ssn=3
	$(CIMCLI) a Person.ssn=4
	$(CIMCLI) a Person.ssn=5
	$(CIMCLI) r Person.ssn=1
	$(CIMCLI) r Person.ssn=2
	$(CIMCLI) r Person.ssn=3
	$(CIMCLI) r Person.ssn=4
	$(CIMCLI) r Person.ssn=5
	$(CIMCLI) rn Person.ssn=1
	$(CIMCLI) rn Person.ssn=2
	$(CIMCLI) rn Person.ssn=3
	$(CIMCLI) rn Person.ssn=4
	$(CIMCLI) rn Person.ssn=5
	call_foo
	call_foo2
	$(CIMCLI) ei Thing
	$(CIMCLI) gi Thing.key=200
	$(CIMCLI) a Thing.key=100
	$(CIMCLI) an Thing.key=100
	$(CIMCLI) r Thing.key=100
	$(CIMCLI) rn Thing.key=100
	$(CIMCLI) ei Lamp
	$(CIMCLI) gi 'Lamp.model="A"'
	$(CIMCLI) an 'Lamp.model="A"'
	$(CIMCLI) rn 'Lamp.model="A"'
	$(CIMCLI) a 'Lamp.model="A"'
	$(CIMCLI) r 'Lamp.model="A"'
	$(CIMCLI) ei Super

endif

genclass:
