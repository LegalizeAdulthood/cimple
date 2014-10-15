ROOT = $(PEGASUS_ROOT)
DIR = cimple/providers/bug31/meth/bug31meth
include $(ROOT)/mak/config.mak
LIBRARIES = pegclient pegcommon

EXTRA_INCLUDES = $(SYS_INCLUDES)

PROGRAM = bug31meth

SOURCES = main.cpp

include $(ROOT)/mak/program.mak

tests:

genclass:

live-tests:
	$(PROGRAM)

chksrc:
	chksrc $(SOURCES)
