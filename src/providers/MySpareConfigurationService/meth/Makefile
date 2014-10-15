TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = MySpareConfigurationService_AssignSpares

SOURCES = main.cpp

LIBRARIES = cimple pegclient pegcommon

INCLUDES += -I$(PEGASUS_INCDIR)

DEFINES += -DPEGASUS_PLATFORM_$(PLATFORM)

include $(TOP)/mak/rules.mak

live:
	$(TARGET)
