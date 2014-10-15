ROOT = $(PEGASUS_ROOT)
DIR = cimple/pegasus/benchmark/Benchmark4
include $(ROOT)/mak/config.mak

LIBRARY = Benchmark4Provider

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

SOURCES = Benchmark4Provider.cpp

LIBRARIES = \
    pegprm \
    pegprovidermanager \
    pegprovider \
    pegconfig \
    pegcommon

INCLUDES += 

CIMPLE_ROOT = ../../../..

include $(CIMPLE_ROOT)/mak/extras.mak
include $(ROOT)/mak/library.mak

reg:
	cimmofl Benchmark4.mof
	cimmofl -n root/PG_InterOp register.mof

