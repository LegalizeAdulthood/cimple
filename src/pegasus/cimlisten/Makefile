TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = cimlisten

SOURCES = main.cpp

LIBRARIES = \
    cimpleutil \
    cimple \
    pegclient \
    peglistener \
    pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

live:
	$(TARGET)

include ../check-pegasus.mak
