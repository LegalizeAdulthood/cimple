ROOT = $(PEGASUS_ROOT)

DIR = cimple/CMPI/providers/Stubs

include $(ROOT)/mak/config.mak

LIBRARY = StubsProvider

SOURCES = StubsProvider.c

EXTRA_INCLUDES += -I$(PEGASUS_ROOT)/src/Pegasus/Provider/CMPI

include $(ROOT)/mak/library.mak

register:
	cimmofl Stubs.mof
	cimmofl -n root/PG_InterOp Registration.mof

genclass:
