TOP = ../../../..
include $(TOP)/mak/config.mak

BINARY = MyIndicationClientListener

SOURCES = MyIndicationClientListener.cpp

LIBRARIES = \
    cimple \
    pegclient \
    peglistener \
    pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

live:
	$(TARGET)

include ../../check-pegasus.mak
