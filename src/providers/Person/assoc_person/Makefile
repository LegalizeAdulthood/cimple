ROOT = $(PEGASUS_ROOT)
DIR = Pegasus/Client/tests/assoc_person
include $(ROOT)/mak/config.mak
LIBRARIES = pegclient pegcommon

EXTRA_INCLUDES = $(SYS_INCLUDES)

PROGRAM = assoc_person

SOURCES = assoc_person.cpp

include $(ROOT)/mak/program.mak

tests:
	$(BIN_DIR)/dlopen $(SHARED_LIBRARY_TARGET)

poststarttests:
