ROOT = $(PEGASUS_ROOT)
DIR = cimple/regmod
include $(ROOT)/mak/config.mak

PROGRAM = regmod

SOURCES = main.cpp

LIBRARIES = \
    cimpleutil \
    cimple \
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
