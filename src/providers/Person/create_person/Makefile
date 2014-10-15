ROOT = $(PEGASUS_ROOT)
DIR = Pegasus/Client/tests/create_person
include $(ROOT)/mak/config.mak
LIBRARIES = pegclient pegcommon

EXTRA_INCLUDES = $(SYS_INCLUDES)

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

PROGRAM = create_person

SOURCES = create_person.cpp

include $(ROOT)/mak/program.mak

tests:

genclass:

chksrc:
	chksrc $(SOURCES)
