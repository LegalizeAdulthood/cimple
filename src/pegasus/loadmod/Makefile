ROOT = $(PEGASUS_ROOT)
DIR = cimple/pegasus/loadmod
include $(ROOT)/mak/config.mak

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

PROGRAM = loadmod

SOURCES = main.cpp

LIBRARIES = \
    pegprovider \
    pegcommon

CIMPLE_ROOT = ../../..
include $(CIMPLE_ROOT)/mak/extras.mak

include $(ROOT)/mak/program.mak

tests:

genclass:

chksrc:
	chksrc $(SOURCES)
