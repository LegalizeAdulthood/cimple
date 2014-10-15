ROOT = $(PEGASUS_ROOT)
DIR = cimple/providers/CIM_StoragePool/meth/CIM_StoragePool_GetAvailableExtents
include $(ROOT)/mak/config.mak
LIBRARIES = pegclient pegcommon

EXTRA_INCLUDES = $(SYS_INCLUDES)

PROGRAM = CIM_StoragePool_GetAvailableExtents

SOURCES = main.cpp

include $(ROOT)/mak/program.mak

tests:

genclass:


live-tests:
	$(PROGRAM)
