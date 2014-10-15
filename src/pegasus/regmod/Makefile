TOP = ../../..
include $(TOP)/mak/config.mak

INSTALL=1

BINARY = regmod

SOURCES = main.cpp

LIBRARIES = cimpleutil cimple pegclient pegcommon

include $(TOP)/mak/pegasus.mak
include $(TOP)/mak/rules.mak

usage:
	$(BINDIR)/file2c usage.txt -n USAGE > usage.h

include ../check-pegasus.mak
