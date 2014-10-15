ROOT = $(PEGASUS_ROOT)
DIR = Pegasus/Client/tests/modify_person
include $(ROOT)/mak/config.mak

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY
LIBRARIES = pegclient pegcommon
EXTRA_INCLUDES = $(SYS_INCLUDES)
PROGRAM = modify_person
SOURCES = modify_person.cpp

include $(ROOT)/mak/program.mak

tests:

poststarttests:

genclass:

chksrc:
	chksrc $(SOURCES)
