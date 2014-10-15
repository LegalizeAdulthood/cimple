ROOT = $(PEGASUS_ROOT)
DIR = cimple/regmod
include $(ROOT)/mak/config.mak

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

PROGRAM = regmod

SOURCES = main.cpp

LIBRARIES = \
    $(CIMPLE_LIBRARY_PREFIX)cimpleutil$(CIMPLE_LIBRARY_SUFFIX) \
    $(CIMPLE_LIBRARY_PREFIX)cimple$(CIMPLE_LIBRARY_SUFFIX) \
    pegprovider \
    pegrepository \
    pegconfig \
    pegcommon

CIMPLE_ROOT = ../../..
include $(CIMPLE_ROOT)/mak/extras.mak

include $(ROOT)/mak/program.mak

usage:
	file2c usage.txt -n USAGE > usage.h

tests:

genclass:
