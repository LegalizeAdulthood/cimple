TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = CIM_StoragePool_GetAvailableExtents

SOURCES = main.cpp

LIBRARIES = cimple pegclient pegcommon

INCLUDES += -I$(PEGASUS_INCDIR)

DEFINES += -DPEGASUS_PLATFORM_$(PLATFORM)

include $(TOP)/mak/rules.mak

live:
	$(TARGET)
