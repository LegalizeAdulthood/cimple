ROOT = $(PEGASUS_ROOT)
DIR = cimple/provmgr/loadpm
include $(ROOT)/mak/config.mak

PROGRAM = loadprovmgr

SOURCES = loadpm.cpp

LIBRARIES = \
    cimpleprovmgr \
    cimpleutil \
    pegprovidermanager \
    pegprovider \
    pegcommon \
    cimpledisp \
    cimple

CIMPLE_ROOT = ../../../..
include $(CIMPLE_ROOT)/mak/extras.mak

include $(ROOT)/mak/program.mak

tests:
