ROOT = $(PEGASUS_ROOT)
DIR = cimple/pegasus/benchmark/Benchmark2
include $(ROOT)/mak/config.mak

LIBRARY = Benchmark2Provider

LOCAL_DEFINES = -DPEGASUS_INTERNALONLY

SOURCES = Benchmark2Provider.cpp

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
	cimmofl Benchmark2.mof
	cimmofl -n root/PG_InterOp register.mof

