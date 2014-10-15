ROOT = $(PEGASUS_ROOT)
DIR = cimple/providers/bug30/meth/bug30meth
include $(ROOT)/mak/config.mak
LIBRARIES = pegclient pegcommon

EXTRA_INCLUDES = $(SYS_INCLUDES)

PROGRAM = bug30meth

SOURCES = main.cpp

include $(ROOT)/mak/program.mak

tests:

genclass:


live-tests:
	$(PROGRAM)

chksrc:
	chksrc $(SOURCES)
