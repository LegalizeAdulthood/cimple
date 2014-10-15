TOP = ../..
include $(TOP)/mak/config.mak

DIRS = \
    repository \
    Person \
    LinuxComputerSystem \
    Example \
    UnixUser \
    Fan \
    Methods \
    MyIndication \
    DerivedIndication

include $(TOP)/mak/dir.mak

ifdef PEGASUS_HOME

DIRS += \
    Person/create_person \
    Person/modify_person \
    Fan/set_speed \
    Methods/foo \
    Methods/foo2

reg:
	( cd Person; make reg )
	( cd Fan; make reg )
	( cd Methods; make reg )
	( cd ComputerSystemDiskDrive; make reg )
	( cd MyIndication; make reg )
	( cd MyIndication; make reg )
	( cd DerivedIndication; make reg )

xxx:
	- CLI gi Person.no_such_property=1

live-tests:
	CLI gi Person.ssn=1
	CLI ni Person
	CLI ni Link
	CLI ni Link
	CLI ni Fan
	CLI ei Person
	CLI ei Link
	CLI ei Link
	CLI ei Fan
	CLI an Person
	CLI an Person.ssn=1
	CLI an Person.ssn=2
	CLI an Person.ssn=3
	CLI an Person.ssn=4
	CLI an Person.ssn=5
	CLI a Person.ssn=1
	CLI a Person.ssn=2
	CLI a Person.ssn=3
	CLI a Person.ssn=4
	CLI a Person.ssn=5
	CLI r Person.ssn=1
	CLI r Person.ssn=2
	CLI r Person.ssn=3
	CLI r Person.ssn=4
	CLI r Person.ssn=5
	CLI rn Person.ssn=1
	CLI rn Person.ssn=2
	CLI rn Person.ssn=3
	CLI rn Person.ssn=4
	CLI rn Person.ssn=5
	call_foo
	call_foo2

endif

genclass:
