ROOT = $(PEGASUS_ROOT)
DIR = cimple/pegasus/benchmark/Benchmark2
include $(ROOT)/mak/config.mak

PROGRAM = Create2

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

SOURCES = main.cpp

LIBRARIES = \
    pegprm \
    pegprovidermanager \
    pegprovider \
    pegconfig \
    pegcommon

INCLUDES +=

CIMPLE_ROOT = ../../../..

include $(CIMPLE_ROOT)/mak/extras.mak
include $(ROOT)/mak/program.mak
